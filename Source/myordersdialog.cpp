#include "myordersdialog.hpp"
#include "ui_myordersdialog.h"

extern QString extern_username;

myOrdersDialog::myOrdersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myOrdersDialog)
{
    ui->setupUi(this);
    QString search = QString("SELECT good_id AS 商品编号,"
                             "good_name AS 商品名称,"
                             "good_price AS 商品价格,"
                             "good_number AS 商品库存,"
                             "user_notice AS 我的备注 FROM orders "
                             "WHERE username='%1'").arg(extern_username);
    qDebug() << search;
    model.setQuery(search);
    ui->tableView->setModel(&model);
}

myOrdersDialog::~myOrdersDialog()
{
    delete ui;
}

void myOrdersDialog::createDB(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    if(db.open()){
        qDebug() << "数据库打开成功";
    }
    else{
        qDebug() << db.lastError().text();
    }
}
