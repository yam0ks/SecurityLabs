#include "TextDialog.h"
#include "FileManager.h"

#include <QFileDialog>

TextDialog::TextDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextDialog)
{
    ui->setupUi(this);
}

void TextDialog::showWindow(Formats format, QIODevice::OpenModeFlag openMode)
{
    ui->textEdit->clear();

    if (m_format != format)
        m_format = format;

    if (m_openMode != openMode)
        m_openMode = openMode;

    show();
}

void TextDialog::on_executeButton_clicked()
{
    QString filePath;

    switch (m_format)
    {
        case Formats::Txt:
            if (m_openMode == QIODevice::WriteOnly)
                filePath = QFileDialog::getSaveFileName(this, "Save file", "", "Txt files(*.txt)");

            else if (m_openMode == QIODevice::Append)
                filePath = QFileDialog::getOpenFileName(this, "Save file", "", "Txt files(*.txt)");
        break;

        case Formats::Xml:
            if (m_openMode == QIODevice::WriteOnly)
                filePath = QFileDialog::getSaveFileName(this, "Save file", "", "Xml files(*.xml)");

            else if (m_openMode == QIODevice::Append)
                filePath = QFileDialog::getOpenFileName(this, "Save file", "", "Xml files(*.xml)");
        break;

        case Formats::Json:
            if (m_openMode == QIODevice::WriteOnly)
                filePath = QFileDialog::getSaveFileName(this, "Save file", "", "Json file(*.json)");

            else if (m_openMode == QIODevice::Append)
                filePath = QFileDialog::getOpenFileName(this, "Save file", "", "Json file(*.json)");
        break;

        default: break;
    }

    if (m_openMode == QIODevice::WriteOnly && !filePath.isEmpty())
    {
        if (!FileManager::createFile(filePath, ui->textEdit->toPlainText()))
            QMessageBox::warning(this, "Attention", "Can't create file");
    }


    else if (m_openMode == QIODevice::Append && !filePath.isEmpty())
    {
       if (!FileManager::changeFileContent(ui->textEdit->toPlainText(), filePath))
           QMessageBox::warning(this, "Attention", "Can't change file content");
    }

    this->close();
}
