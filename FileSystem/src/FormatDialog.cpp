#include "FormatDialog.h"

#include "FileManager.h"

#include <QFileDialog>

FormatDialog::FormatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormatDialog)
{
    ui->setupUi(this);
}

void FormatDialog::showWindow(Formats format)
{
    ui->ageEdit->clear();
    ui->nameEdit->clear();
    ui->courseEdit->clear();
    ui->specialityEdit->clear();

    if (m_format != format)
        m_format = format;

    show();
}

void FormatDialog::on_executeButton_clicked()
{
    QString filePath;

    switch (m_format)
    {
        case Formats::Txt:
            filePath = QFileDialog::getSaveFileName(this, "Save file", "", "Txt files(*.txt)");
        break;

        case Formats::Xml:
            filePath = QFileDialog::getSaveFileName(this, "Save file", "", "Xml files(*.xml)");
        break;

        case Formats::Json:
            filePath = QFileDialog::getSaveFileName(this, "Save file", "", "Json file(*.json)");
        break;

        default: break;
    }

    const Example::Student student = {
        ui->nameEdit->text().simplified(),
        ui->specialityEdit->text().simplified(),
        ui->ageEdit->text().simplified().toInt(),
        ui->courseEdit->text().simplified().toInt()
    };

    if (m_format == Formats::Xml && !FileManager::createFile(filePath, FormatParser::serializeToXml(student)) && !filePath.isEmpty())
        QMessageBox::warning(this, "Attention", "Can't serialize object");

    if (m_format == Formats::Json && !FileManager::createFile(filePath, FormatParser::serializeToJson(student)) && !filePath.isEmpty())
        QMessageBox::warning(this, "Attention", "Can't serialize object");

    this->close();
}
