#ifndef REGISTERDIALOG_HPP
#define REGISTERDIALOG_HPP

#include <QDialog>
#include "QMessageBox"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QSqlRecord>
#include <QValidator>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_cancelButton_clicked();

    void on_registerButton_clicked();

private:
    Ui::RegisterDialog *ui;
    QSqlDatabase db;
    void createDB();
};

#endif // REGISTERDIALOG_HPP
