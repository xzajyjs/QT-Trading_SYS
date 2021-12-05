#include "myprofiledialog.hpp"
#include "ui_myprofiledialog.h"

extern QString extern_username;
extern QString extern_address;
extern QString extern_phone;

myProfileDialog::myProfileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myProfileDialog)
{
    ui->setupUi(this);
    ui->phoneEdit->setValidator(new QIntValidator(this));
    createDB();
    InitInfo();
}

myProfileDialog::~myProfileDialog()
{
    delete ui;
}

void myProfileDialog::createDB(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    if(db.open()){
        qDebug() << "数据库打开成功";
    }
    else{
        qDebug() << db.lastError().text();
    }
}

void myProfileDialog::InitInfo(){
    QSqlQuery query;
    QString str;


    ui->usernameEdit->setText(extern_username);
    ui->phoneEdit->setText(extern_phone);
    ui->addressEdit->setText(extern_address);
}

// 修改按钮
void myProfileDialog::on_changeButton_clicked()
{
    // 激活
    if(ui->changeButton->text() == "修改"){
        ui->changeButton->setText("确定");
        ui->phoneEdit->setEnabled(true);
        ui->addressEdit->setEnabled(true);
    }
    // 激活应用
    else{
        QString new_phone = ui->phoneEdit->text();
        QString new_address = ui->addressEdit->text();
        QString query_str = QString("UPDATE users "
                                    "SET phone='%1', address='%2'"
                                    "WHERE username='%3'")
                .arg(new_phone).arg(new_address).arg(extern_username);
        QSqlQuery query;
        if(query.exec(query_str)){
            qDebug() << "信息更新成功";
            QMessageBox msg;
            msg.setText("信息修改成功");
            msg.exec();
            this->close();
        }
        else{
            qDebug() << "信息修改失败:" << query_str;
        }
    }



}

