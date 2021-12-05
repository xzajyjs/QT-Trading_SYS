#include "forgetpasswddialog.hpp"
#include "ui_forgetpasswddialog.h"

forgetPasswdDialog::forgetPasswdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forgetPasswdDialog)
{
    ui->setupUi(this);
    createDB();
}

forgetPasswdDialog::~forgetPasswdDialog()
{
    delete ui;
}

void forgetPasswdDialog::createDB(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    if(db.open()){
        qDebug() << "数据库打开成功";
    }
    else{
        qDebug() << db.lastError().text();
    }
}

void forgetPasswdDialog::on_changeButton_clicked()
{
    QString input_first_passwd = ui->newFirst_passwd->text();
    QString input_second_passwd = ui->newSec_passwd->text();
    QString input_username = ui->new_username->text();

    if(input_username == ""){
        QMessageBox msg;msg.setText("账号为空");msg.exec();
    }
    else if(input_first_passwd != input_second_passwd){
        QMessageBox msg;msg.setText("密码输入不一致");msg.exec();
    }
    else{
        QSqlQuery query;
        QString str = QString("SELECT username FROM users "
                                 "WHERE username='%1'").arg(input_username);
        query.exec(str);
        query.next();
        // 找到了同名用户
        if(query.value(0).toString() != input_username){
            QMessageBox msg;
            msg.setText("不存在该用户");
            msg.exec();
        }
        else{
            str = QString("UPDATE users SET password='%1' WHERE username='%2';").arg(input_first_passwd).arg(input_username);
            query.exec(str);
            QMessageBox msg;msg.setText("密码修改成功");msg.exec();
            this->close();
        }
    }
}

void forgetPasswdDialog::on_cancelButton_clicked()
{
    this->close();
}

