#include "releasegoodsdialog.hpp"
#include "ui_releasegoodsdialog.h"
#include "menuwidget.hpp"
#include "mainwindow.h"

QString extern_from;
extern QString extern_commodity;

ReleaseGoodsDialog::ReleaseGoodsDialog(const QString &from, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReleaseGoodsDialog)
{
    extern_from = from;
    ui->setupUi(this);
    ui->idEdit->setValidator(new QIntValidator(this));
    ui->priceEdit->setValidator(new QIntValidator(this));
    ui->releaseButton->setFocus();
    createDB();
}

ReleaseGoodsDialog::~ReleaseGoodsDialog()
{
    delete ui;
}

void ReleaseGoodsDialog::createDB(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    if(db.open()){
        qDebug() << "数据库打开成功!";
    }
    else{
        qDebug() << db.lastError().text();
    }
}

void ReleaseGoodsDialog::on_releaseButton_clicked()
{
    int _id = ui->idEdit->text().toInt();
    QString _name = ui->nameEdit->text();
    double _price = ui->priceEdit->text().toDouble();
    int _number = ui->numberEdit->text().toInt();
    QString _notice = ui->noticeEdit->text();

    QSqlQuery query;
    // 判断是否有这个商品编号了
    QString search = QString("SELECT 编号 FROM goods "
                             "WHERE 编号='%1'").arg(ui->idEdit->text());
    query.exec(search);
    query.next();
    // 找到了同名编号
    if(query.value(0).toString() == ui->idEdit->text()){
        QMessageBox msg;
        msg.setText("编号已存在!");
        msg.exec();
    }
    else{
        QString str = QString("INSERT INTO goods(编号,名称,价格,数量,备注)"
                              "VALUES(%1,'%2',%3,%4,'%5')").arg(_id).arg(_name)
                .arg(_price).arg(_number).arg(_notice);
        if(query.exec(str)){
            qDebug() << "商品发布成功!";
            if(extern_from == "admin"){
                QMessageBox msg;
                msg.setText("商品发布成功!");
                msg.exec();
                MainWindow *mainwindow = new MainWindow(extern_commodity);
                mainwindow->show();
                this->close();
            }
            else if(extern_from == "user"){
                MenuWidget *menu = new MenuWidget;
                QMessageBox msg;
                msg.setText("商品发布成功!");
                msg.exec();
                menu->show();
                this->close();
            }
        }
        else{
            qDebug() << str;
        }
    }
}


void ReleaseGoodsDialog::on_cancelButton_clicked()
{
    if(extern_from == "admin"){
        MainWindow *mainwindow = new MainWindow(extern_commodity);
        mainwindow->show();
        this->close();
    }
    else if(extern_from == "user"){
        MenuWidget *menu = new MenuWidget;
        menu->show();
        this->close();
    }
}

