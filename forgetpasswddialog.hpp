#ifndef FORGETPASSWDDIALOG_HPP
#define FORGETPASSWDDIALOG_HPP

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QSqlRecord>

namespace Ui {
class forgetPasswdDialog;
}

class forgetPasswdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit forgetPasswdDialog(QWidget *parent = nullptr);
    ~forgetPasswdDialog();

private slots:
    void on_changeButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::forgetPasswdDialog *ui;
    QSqlDatabase db;
    void createDB();
};

#endif // FORGETPASSWDDIALOG_HPP
