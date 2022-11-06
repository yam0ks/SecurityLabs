#include "Console.h"

#include "DiskManager.h"
#include "FileManager.h"

#include "TextDialog.h"
#include "FormatDialog.h"
#include "ZipDialog.h"

#include <QKeyEvent>
#include <QStorageInfo>
#include <QFileDialog>

#include <optional>

Console::Console(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Console)
    , m_textDialog(new TextDialog(this))
    , m_formatDialog(new FormatDialog(this))
    , m_zipDialog(new ZipDialog(this))
{
    ui->setupUi(this);

    connect(ui->actionDI, &QAction::triggered, this, &Console::printVolumesInfo);

    connect(ui->actionTxtCreate, &QAction::triggered, this, &Console::createTxtFile);
    connect(ui->actionTxtWrite,  &QAction::triggered, this, &Console::appendTxtFile);

    connect(ui->actionJsonCreate,    &QAction::triggered, this, &Console::createJsonFile);
    connect(ui->actionJsonSerialize, &QAction::triggered, this, &Console::serializeObjectToJson);

    connect(ui->actionXmlCreate,    &QAction::triggered, this, &Console::createXmlFile);
    connect(ui->actionXmlSerialize, &QAction::triggered, this, &Console::serializeObjectToXml);

    connect(ui->actionZipCreate, &QAction::triggered, this, &Console::createZip);
    connect(ui->actionZipAdd,    &QAction::triggered, this, &Console::addFileToZip);
    connect(ui->actionZipUnzip,  &QAction::triggered, this, &Console::unzipFile);
    connect(ui->actionZipRemove, &QAction::triggered, this, &Console::deleteZippedFile);

    connect(ui->actionDelete, &QAction::triggered, this, &Console::deleteFile);
    connect(ui->actionOpen,   &QAction::triggered, this, &Console::readFile);
}

void Console::printVolumesInfo()
{
    ui->console->setText(DiskManager::logicDisksInfoToStr());
}

void Console::createTxtFile()
{
    m_textDialog->showWindow(Formats::Txt, QIODevice::WriteOnly);
}

void Console::appendTxtFile()
{
    m_textDialog->showWindow(Formats::Txt, QIODevice::Append);
}

void Console::createJsonFile()
{
    m_textDialog->showWindow(Formats::Json, QIODevice::WriteOnly);
}

void Console::serializeObjectToJson()
{
    m_formatDialog->showWindow(Formats::Json);
}

void Console::createXmlFile()
{
    m_textDialog->showWindow(Formats::Xml, QIODevice::WriteOnly);
}

void Console::serializeObjectToXml()
{
    m_formatDialog->showWindow(Formats::Xml);
}

void Console::createZip()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save zip", "", "Zip files(*.zip)");

    if (!FileManager::createArchive(filePath) && !filePath.isEmpty())
        QMessageBox::warning(this, "Attention", "Can't create archive");
}

void Console::addFileToZip()
{
    QString zipPath = QFileDialog::getOpenFileName(this, "Open File", "", "Zip files(*.zip)");

    if (zipPath.isEmpty())
        return;

    QString filePath = QFileDialog::getOpenFileName(this, "OpenFile", "",
                                                    "Txt files(*.txt);;Xml files(*.xml);;Json files(*.json)");

    if (!FileManager::zipFile(zipPath, filePath) && !zipPath.isEmpty() && !filePath.isEmpty())
        QMessageBox::warning(this, "Attention", "File can't be zipped");
}

void Console::unzipFile()
{
    QString zipFilePath = QFileDialog::getOpenFileName(this, "Open zip", "", "Zip files(*.zip)");
    QVector<QString> zipFilesNames = FileManager::zipFilesNames(zipFilePath);

    if (!zipFilePath.isEmpty() && zipFilesNames.isEmpty())
    {
        QMessageBox::warning(this, "Attention", "Archive is empty");
        return;
    }

    if (zipFilePath.isEmpty())
        return;

    QString fileNames;

    for (const QString& file : zipFilesNames)
        fileNames += file + "\n";

    m_zipDialog->setBrowserText(fileNames);
    m_zipDialog->setZipPath(zipFilePath);

    m_zipDialog->showWindow();
    m_zipDialog->setActionType(ZipActions::Actions::UnzipFile);
}

void Console::deleteZippedFile()
{
    QString zipFilePath = QFileDialog::getOpenFileName(this, "Open zip", "", "Zip files(*.zip)");
    QVector<QString> zipFilesNames = FileManager::zipFilesNames(zipFilePath);

    if (!zipFilePath.isEmpty() && zipFilesNames.isEmpty())
    {
        QMessageBox::warning(this, "Attention", "Archive is empty");
        return;
    }

    if (zipFilePath.isEmpty())
        return;

    QString fileNames;

    for (const QString& file : zipFilesNames)
        fileNames += file + "\n";

    m_zipDialog->setBrowserText(fileNames);
    m_zipDialog->setZipPath(zipFilePath);

    m_zipDialog->showWindow();
    m_zipDialog->setActionType(ZipActions::Actions::RemoveFile);
}

void Console::deleteFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Remove file", "",
                                                    "Txt files(*.txt);;Xml files(*.xml);;Json files(*.json)");

    if (!FileManager::deleteFile(filePath) && !filePath.isEmpty())
        QMessageBox::warning(this, "Attention", "File can't be remove");
}

void Console::readFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open file", "",
                                                    "Txt files(*.txt);;Xml files(*.xml);;Json files(*.json)");

    auto result = FileManager::readFile(filePath);

    if (result.has_value() && !filePath.isEmpty())
        ui->console->setText(result.value());
    else if (!filePath.isEmpty())
        QMessageBox::warning(this, "Attention", "File can't be read");
}

void Console::fileUnzipHandler(std::optional<QString> data)
{
    if (!data.has_value())
    {
        QMessageBox::warning(this, "Attention", "File can't be unzipped");
        return;
    }

    ui->console->setText(data.value());
}

void Console::fileRemoveHandler(bool succed)
{
    if (!succed)
        QMessageBox::warning(this, "Attention", "File can't be removed from zip");
}
