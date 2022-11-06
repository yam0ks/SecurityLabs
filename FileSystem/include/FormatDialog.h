#pragma once

#include "ui_FormatDialog.h"
#include "FormatParser.h"

#include <QDialog>

class FormatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FormatDialog(QWidget *parent = nullptr);
    ~FormatDialog() = default;

public slots:
    void showWindow(Formats format);

private slots:
    void on_executeButton_clicked();

private:
    QSharedPointer<Ui::FormatDialog> ui;

    Formats m_format;
};
