#include "logindialog.hpp"
#include "ui_logindialog.h"
#include "QMessageBox"
#include "menuwidget.hpp"
#include "registerdialog.hpp"
#include "forgetpasswddialog.hpp"
#include "chosetabledialog.hpp"

QString extern_username;

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->radioButton->setChecked(false);
    createDB();
    createTable();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::createDB(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    if(db.open()){
        qDebug() << "数据库打开成功";
        ui->radioButton->setChecked(true);
    }
    else{
        qDebug() << db.lastError().text();
        ui->radioButton->setChecked(false);
    }
}

// id(PK), username(TEXT), password(TEXT), phone(TEXT), address(TEXT)
void LoginDialog::createTable(){
    QSqlQuery query;
    QString str = QString("CREATE TABLE users("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                          "username TEXT NOT NULL,"
                          "password TEXT NOT NULL,"
                          "phone TEXT,"
                          "address TEXT);");
    if(query.exec(str)){
        qDebug() << "数据表创建成功";
    }
    else{
        qDebug() << str;
    }

    // 创建初始管理员用户: admin / 123456
    QString search = QString("SELECT username FROM users "
                             "WHERE username='admin'");
    query.exec(search);query.next();
    // 找到了admin
    if(query.value(0).toString() == "admin"){
        qDebug() << "admin已存在";
    }
    else{
        str = QString("INSERT INTO users(username, password, phone, address) VALUES("
                      "'admin', '123456', '17912313323', '江苏省南京浦口区宁六路219号');");
        if(query.exec(str)){
            qDebug() << "初始数据创建完成";
        }
        else{
            qDebug() << str;
        }
    }

    // 创建初始普通用户: test / 123456
    search = QString("SELECT username FROM users "
                             "WHERE username='test'");
    query.exec(search);query.next();
    // 找到了test
    if(query.value(0).toString() == "test"){
        qDebug() << "test已存在";
    }
    else{
        str = QString("INSERT INTO users(username, password, phone, address) VALUES("
                      "'test', '123456', '13812122222', '江苏省南京浦口区宁六路219号');");
    }
    query.exec(str);

    // 创建初始普通用户: haha123 / haha123
    search = QString("SELECT username FROM users "
                             "WHERE username='haha123'");
    query.exec(search);query.next();
    if(query.value(0).toString() == "haha123"){
        qDebug() << "haha123已存在";
    }
    else{
        str = QString("INSERT INTO users(username, password, phone, address) VALUES("
                      "'haha123', 'haha123', '15312980744', '东方明珠塔下');");
    }
    query.exec(str);
}

void LoginDialog::on_loginButton_clicked()
{
    QString input_password = ui->password->text();
    QString input_username = ui->username->text();


    if(input_username == ""){
        QMessageBox msg;
        msg.setText("账号为空");
        msg.exec();
    }
    else if(input_password == ""){
        QMessageBox msg;
        msg.setText("密码为空");
        msg.exec();
    }
    // 账号密码都非空
    else{
        QSqlQuery query;
        QString str = QString("SELECT password FROM users WHERE username='%1'").arg(input_username);
        if(!query.exec(str)){
            qDebug() << str;
        }
        /**/
        query.next();
        qDebug() << "密码是:" << query.value(0).toString();
        /**/
        // 账号密码正确
        if(input_password == query.value(0).toString()){
            extern_username = input_username;
            if(input_username == "admin"){
                // 生成管理员后台
                choseTableDialog *choose = new choseTableDialog;
                this->close();
                choose->show();
            }
            else{
                // 生成用户界面主菜单
                MenuWidget *menu = new MenuWidget;
                QMessageBox msg;
                msg.setText("登陆成功");
                msg.exec();
                menu->show();
                this->close();
            }
        }
        // 账号或密码不正确
        else{
            QMessageBox msg;
            msg.setText("账号或密码错误");
            msg.exec();
        }
    }
}
void LoginDialog::on_registerButton_clicked()
{
    RegisterDialog *registerDialog = new RegisterDialog;
    registerDialog->show();
}

void LoginDialog::on_forgetButton_clicked()
{
    forgetPasswdDialog *forget = new forgetPasswdDialog;
    forget->show();
}

