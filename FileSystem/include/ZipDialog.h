#pragma once

#include "ui_ZipDialog.h"
#include "FormatParser.h"

#include <QDialog>
#include <optional>

namespace ZipActions
{
    enum Actions
    {
        UnzipFile,
        RemoveFile,
    };
}

class ZipDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZipDialog(QWidget *parent = nullptr);
    ~ZipDialog() = default;

public slots:
    void executeButtonClicked();
    void setActionType(ZipActions::Actions actionType);
    void setZipPath(const QString& zipPath);
    void setBrowserText(const QString& text);
    void showWindow();
signals:
    void fileRemoved(bool);
    void fileUnzipped(std::optional<QString>);

private:
    QSharedPointer<Ui::ZipDialog> ui;

    ZipActions::Actions m_action;
    QString m_zipPath;
};
