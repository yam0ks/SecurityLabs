#pragma once

#include "ui_TextDialog.h"
#include "FormatParser.h"

#include <QDialog>

class TextDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextDialog(QWidget *parent = nullptr);
    ~TextDialog() = default;

public slots:
    void showWindow(Formats format, QIODevice::OpenModeFlag openMode);

private slots:
    void on_executeButton_clicked();

private:
    QSharedPointer<Ui::TextDialog> ui;

    QIODevice::OpenModeFlag m_openMode = QIODevice::WriteOnly;
    Formats m_format;
};
