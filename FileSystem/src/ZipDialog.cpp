#include "ZipDialog.h"
#include "FileManager.h"

#include <QFileDialog>

ZipDialog::ZipDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ZipDialog)
{
    ui->setupUi(this);

    connect(ui->executeButton, &QPushButton::clicked, this, &ZipDialog::executeButtonClicked);
}

void ZipDialog::executeButtonClicked()
{
    switch (m_action)
    {
        case ZipActions::Actions::RemoveFile:
            emit fileRemoved(FileManager::removeZippedFile(m_zipPath, ui->fileNameEdit->text()));
        break;

        case ZipActions::Actions::UnzipFile:
            emit fileUnzipped(FileManager::unzipFile(m_zipPath, ui->fileNameEdit->text()));
        break;
    }

    this->close();
}

void ZipDialog::setActionType(ZipActions::Actions actionType)
{
    if (m_action != actionType)
        m_action = actionType;
}

void ZipDialog::setZipPath(const QString &zipPath)
{
    if (m_zipPath != zipPath)
        m_zipPath = zipPath;
}

void ZipDialog::setBrowserText(const QString &text)
{
    ui->textBrowser->setText(text);
}

void ZipDialog::showWindow()
{
    ui->fileNameEdit->clear();
    show();
}
