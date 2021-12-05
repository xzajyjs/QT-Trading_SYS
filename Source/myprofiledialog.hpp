#ifndef MYPROFILEDIALOG_HPP
#define MYPROFILEDIALOG_HPP

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QValidator>

namespace Ui {
class myProfileDialog;
}

class myProfileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit myProfileDialog(QWidget *parent = nullptr);
    ~myProfileDialog();

private slots:
    void on_changeButton_clicked();

private:
    void createDB();
    void InitInfo();    // 初始化显示信息

private:
    Ui::myProfileDialog *ui;
    QSqlDatabase db;


};

#endif // MYPROFILEDIALOG_HPP
