#pragma once

#include <QFileInfo>
#include <QMessageBox>

#include <optional>

class FileManager
{
public:
    FileManager() = default;
    ~FileManager() = default;

public:
    static bool createFile (const QString& path, const QString& content);
    static bool changeFileContent(const QString& content, const QString& path);
    static bool deleteFile(const QString& path);
    static std::optional<QString> readFile(const QString& path);

    static bool createArchive(const QString& path);
    static bool zipFile(const QString& zipPath, const QString& filePath);
    static std::optional<QString> unzipFile(const QString& zipPath, const QString& fileName);
    static bool removeZippedFile(const QString& zipPath, const QString& fileName);
    static QVector<QString> zipFilesNames(const QString& zipFilePath);

private:
    static bool writeToFile(const QString& content, const QString& path, QIODevice::OpenModeFlag openMode);
};
