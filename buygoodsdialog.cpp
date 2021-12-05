#include "buygoodsdialog.hpp"
#include "ui_buygoodsdialog.h"

extern int extern_id;
extern QString extern_username;
extern QString extern_address;
extern QString extern_phone;

buyGoodsDialog::buyGoodsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::buyGoodsDialog)
{
    createDB();
    createTable();
    ui->setupUi(this);
    QSqlQuery query;
    QString str;
    qDebug() << "购买的id为:" << extern_id;

    str = QString::number(extern_id);
    ui->idLineEdit->setText(str);
    str = QString("SELECT 名称 FROM goods WHERE 编号=%1").arg(extern_id);
    query.exec(str);query.next();
    ui->nameLineEdit->setText(query.value(0).toString());
    str = QString("SELECT 价格 FROM goods WHERE 编号=%1").arg(extern_id);
    query.exec(str);query.next();
    ui->priceLineEdit->setText(query.value(0).toString());
    str = QString("SELECT 数量 FROM goods WHERE 编号=%1").arg(extern_id);
    query.exec(str);query.next();
    ui->numberLineEdit->setText(query.value(0).toString());
    str = QString("SELECT 备注 FROM goods WHERE 编号=%1").arg(extern_id);
    query.exec(str);query.next();
    ui->noticeLineEdit->setText(query.value(0).toString());
    ui->addressLineEdit->setText(extern_address);
    ui->phoneLineEdit->setText(extern_phone);
}

buyGoodsDialog::~buyGoodsDialog()
{
    delete ui;
}

void buyGoodsDialog::createDB(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    if(db.open()){
        qDebug() << "数据库打开成功";
    }
    else{
        qDebug() << db.lastError().text();
    }
}

// 创建订单数据表
// id 序号(自动递进), good_id 商品编号, username 用户名,
// good_name 商品名称, good_price 商品价格, good_number 商品数量, user_notice 购买者备注
void buyGoodsDialog::createTable(){
    QSqlQuery query;
    QString str = QString("CREATE TABLE orders("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                          "good_id INT NOT NULL,"
                          "username TEXT NOT NULL,"
                          "good_name TEXT NOT NULL,"
                          "good_price DOUBLE NOT NULL,"
                          "good_number INT NOT NULL,"
                          "user_notice TEXT);");
    if(query.exec(str)){
        qDebug() << "创建order数据表成功";
    }
    else{
        qDebug() << str;
    }
}

// 取消
void buyGoodsDialog::on_pushButton_2_clicked()
{
    this->close();
}

// 购买
void buyGoodsDialog::on_pushButton_clicked()
{
    QSqlQuery query;
    QString str;
    QString good_name, user_notice;
    int good_number;
    double good_price;
    // 获取good_name, good_price, good_number, user_notice
    str = QString("SELECT 名称 FROM goods WHERE 编号=%1").arg(extern_id);
    query.exec(str);query.next();
    good_name = query.value(0).toString();
    str = QString("SELECT 价格 FROM goods WHERE 编号=%1").arg(extern_id);
    query.exec(str);query.next();
    good_price = query.value(0).toDouble();
    str = QString("SELECT 数量 FROM goods WHERE 编号=%1").arg(extern_id);
    query.exec(str);query.next();
    good_number = query.value(0).toInt();
    user_notice = ui->buyLineEdit->text();
    qDebug() << "user_notice is :" << user_notice;

    str = QString("INSERT INTO orders(good_id, username, good_name, good_price, good_number, user_notice) "
                  "VALUES(%1, '%2', '%3', %4, %5, '%6');")
            .arg(extern_id).arg(extern_username).arg(good_name)
            .arg(good_price).arg(good_number).arg(user_notice);
    if(query.exec(str)){
        qDebug() << "订单创建成功";
        QMessageBox msg;
        msg.setText("购买成功");
        msg.exec();
        this->close();
    }
    else{
        qDebug() << str;
    }
}

