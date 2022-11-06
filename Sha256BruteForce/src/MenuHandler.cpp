#include "MenuHandler.h"

#include "Sha256Gen.h"

#include <QFileInfo>
#include <QTextStream>
#include <QElapsedTimer>
#include <QIODevice>

void MenuHandler::execStartMenu()
{
    QString menu = "====================\n"
                   "0. Exit\n"
                   "1. Read from console\n"
                   "2. Read from file\n"
                   "====================\n\n";

    QTextStream output(stdout);
    (output << menu).flush();

    QString currentChoice;

    while (true)
    {
        (output << ">").flush();

        currentChoice = QTextStream(stdin).readLine();

        if (currentChoice == "1")
        {
            execBruteForce(InputType::Stream);
            (output << menu).flush();
        }

        else if (currentChoice == "2")
        {
            execBruteForce(InputType::File);
            (output << menu).flush();
        }

        else if (currentChoice == "0")
            break;
    }
}

void MenuHandler::execBruteForce(InputType type)
{
    QStringList hashes = type == InputType::Stream ? readFromStream()
                                                   : readFromFile();

    QTextStream(stdout) << "\nInput threads count\n\n" << ">";
    int threadCount = QTextStream(stdin).readLine().toInt();
    QTextStream(stdout) << "\n";

    QElapsedTimer timer;
    timer.start();
    auto bruttedMap = Sha256Gen::bruteForce(hashes, threadCount);
    int64_t time = timer.elapsed();

    for (const QString& key : bruttedMap.keys())
        QTextStream(stdout) << key << ": " << bruttedMap.value(key) << "\n";

    QTextStream(stdout) << "Time spent: " << time << " msec\n\n";
}

QStringList MenuHandler::readFromFile()
{
    QTextStream(stdout) << "\nInput file path\n\n" << ">";
    QString filePath = QTextStream(stdin).readLine();

    QFile file(filePath);

    if (QFileInfo(filePath).suffix() != "txt" || !file.open(QIODevice::ReadOnly))
        return {};

    QStringList hashes = QString(file.readAll()).split(QRegExp("[\r\n]"),QString::SkipEmptyParts);

    file.close();

    return hashes;
}

QStringList MenuHandler::readFromStream()
{
    QTextStream(stdout) << "\nInput hashes or press enter to stop:\n\n";

    QStringList hashes;
    QTextStream input(stdin);

    while (true)
    {
        QTextStream(stdout) << ">";
        QString line(input.readLine());

        if (line.isEmpty())
            break;

        hashes.append(line);
    }

    return hashes;
}
