
#include "Sha256Gen.h"

#include <QtConcurrent>
#include <string_view>
#include <mutex>

struct Task
{
    int64_t offset;
    int64_t size;
    QFile* file;
    QString hash;
};

std::mutex m;

QMultiMap<QString, QString> Sha256Gen::bruteForce(const QStringList& hashes, int threadCount)
{
    QFile* file = new QFile("map.txt");

    if (!file->open(QIODevice::ReadWrite))
        return {};

    QMultiMap<QString, QString> result;

    for (const QString& hash : hashes)
        result.insert(hash, bruteForceImpl(hash, threadCount, file));

    file->close();
    delete file;

    return result;
}

QString Sha256Gen::bruteForceImpl(const QString& hash, int threadCount, QFile* file)
{
    constexpr int lineLength = 71;

    const int64_t linesCount = file->size() / lineLength;
    const int taskLinesCount = linesCount / (threadCount == 0 ? 1 : threadCount);

    int64_t offset = 0;
    int64_t size = lineLength * taskLinesCount;

    QVector<Task> tasks;
    tasks.reserve(threadCount == 0 ? 1 : threadCount);

    while (offset < file->size())
    {
        if (offset + size >= file->size())
            tasks.push_back({offset, file->size() - offset, file, hash});

        else
            tasks.push_back({offset, size, file, hash});

        offset += size;
    }

    QString result = QtConcurrent::blockingMappedReduced(tasks, threadForce, reduceResult);

    return result.isEmpty() ? "Bad hash :(" : result;
}

QString Sha256Gen::threadForce(const Task& task)
{
    uchar* rawLine;

    {
        std::lock_guard<std::mutex> lock(m);
        rawLine = task.file->map(task.offset, task.size);
    }

    std::string_view data = std::string_view(reinterpret_cast<char*>(rawLine), task.size);;

    constexpr int lineLength = 71;
    constexpr int hashLength = 64;
    constexpr int enctyptedLength = 5;
    const int64_t linesCount = task.size / lineLength;

    int left = 0;
    int right = linesCount;
    int mid;

    QString result;

    while (left <= right)
    {
        mid = (left + right) / 2;
        std::string_view val = data.substr(mid * lineLength, hashLength);

        if (val == task.hash.toStdString())
        {
            result = QString::fromUtf8(data.substr(mid * lineLength + hashLength + 1, enctyptedLength).data(), enctyptedLength);
            break;
        }

        else if(val < task.hash.toStdString())
            left = mid + 1;

        else if (val > task.hash.toStdString())
            right = mid - 1;
    }

    {
        std::lock_guard<std::mutex> lock(m);
        task.file->unmap(rawLine);
    }

    return result;
}

void Sha256Gen::reduceResult(QString& result, const QString& local)
{
    result = local.isEmpty() ? result : local;
}
