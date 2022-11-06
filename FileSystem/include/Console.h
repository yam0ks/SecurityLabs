#pragma once

#include "ui_Console.h"

#include <QMainWindow>
#include <optional>

class TextDialog;
class FormatDialog;
class ZipDialog;

class Console : public QMainWindow
{
    Q_OBJECT

public:
    Console(QWidget *parent = nullptr);
    ~Console() = default;

private slots:
    void printVolumesInfo();

    void createTxtFile();
    void appendTxtFile();

    void createJsonFile();
    void serializeObjectToJson();

    void createXmlFile();
    void serializeObjectToXml();

    void createZip();
    void addFileToZip();
    void unzipFile();
    void deleteZippedFile();

    void deleteFile();
    void readFile();

    void fileUnzipHandler(std::optional<QString> data);
    void fileRemoveHandler(bool succed);

private:
    QSharedPointer<Ui::Console> ui;

    TextDialog* m_textDialog;
    FormatDialog* m_formatDialog;
    ZipDialog* m_zipDialog;
};
