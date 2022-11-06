#include "FileManager.h"
#include "FormatParser.h"

#include "libzippp.h"

#include <QDebug>

bool FileManager::createFile(const QString& path, const QString& content)
{
    return writeToFile(content, path, QIODevice::WriteOnly);
}

bool FileManager::changeFileContent(const QString& content, const QString& path)
{
    return writeToFile(content, path, QIODevice::Append);
}

bool FileManager::deleteFile(const QString& path)
{
    if (!QFile::remove(path))
        return false;

    return true;
}

std::optional<QString> FileManager::readFile(const QString& path)
{
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly))
        return {};

    QString result = file.readAll();
    file.close();

    return result;
}

bool FileManager::createArchive(const QString& path)
{
        libzippp::ZipArchive zip(path.toStdString());

        if (!zip.open(libzippp::ZipArchive::New))
            return false;

        zip.close();

        return true;
}

bool FileManager::zipFile(const QString &zipPath, const QString &filePath)
{
    libzippp::ZipArchive zip(zipPath.toStdString());

    if (!zip.open(libzippp::ZipArchive::Write))
        return false;

    if (!zip.addFile(QFileInfo(filePath).fileName().toStdString(), filePath.toStdString()))
    {
        zip.close();
        return false;
    }

    zip.close();
    return true;
}

std::optional<QString> FileManager::unzipFile(const QString &zipPath, const QString &fileName)
{
    libzippp::ZipArchive zip(zipPath.toStdString());

    if (!zip.open(libzippp::ZipArchive::Write))
        return {};

    libzippp::ZipEntry entry = zip.getEntry(fileName.toStdString());

    if (entry.isNull())
        return {};

    QString data = QString::fromStdString(entry.readAsText());

    zip.deleteEntry(entry);
    zip.close();

    QString filePath = QFileInfo(zipPath).path() + "/" + QFileInfo(fileName).baseName();

    while (QFileInfo(filePath + "." + QFileInfo(fileName).suffix()).exists())
        filePath += QString::number(1);

    filePath += "." + QFileInfo(fileName).suffix();

    qWarning() << filePath;

    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly))
        return {};

    file.write(data.toUtf8());

    file.close();

    return data;
}

bool FileManager::removeZippedFile(const QString &zipPath, const QString &fileName)
{
    libzippp::ZipArchive zip(zipPath.toStdString());

    if (!zip.open(libzippp::ZipArchive::Write))
        return false;

    if (!zip.deleteEntry(fileName.toStdString()))
        return false;

    zip.close();
    return true;
}

QVector<QString> FileManager::zipFilesNames(const QString &zipFilePath)
{
    libzippp::ZipArchive zip(zipFilePath.toStdString());

    if (!zip.open(libzippp::ZipArchive::Write))
        return {};

    auto entries = zip.getEntries();

    QVector<QString> result;

    std::transform(entries.begin(), entries.end(), std::back_inserter(result),
                   [](const libzippp::ZipEntry& entry){
        return QString::fromStdString(entry.getName());
    });

    return result;
}

bool FileManager::writeToFile(const QString& content, const QString& path, QIODevice::OpenModeFlag openMode)
{
    if (QFileInfo(path).suffix() == "json" && !FormatParser::validJson(content))
        return false;

    if (QFileInfo(path).suffix() == "xml" && !FormatParser::validXml(content))
        return false;

    QFile file(path);

    if ((openMode != QIODevice::WriteOnly && openMode != QIODevice::Append) || !file.open(openMode))
        return false;

    file.write(content.toUtf8());
    file.close();

    return true;
}
