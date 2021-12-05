#include "chosetabledialog.hpp"
#include "ui_chosetabledialog.h"
#include "mainwindow.h"
#include "logindialog.hpp"

choseTableDialog::choseTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::choseTableDialog)
{
    ui->setupUi(this);
}

choseTableDialog::~choseTableDialog()
{
    delete ui;
}

void choseTableDialog::on_pushButton_clicked()
{
    if(ui->comboBox->currentText() == "用户管理"){
        MainWindow *users_control = new MainWindow("users");
        users_control->show();
    }
    else if(ui->comboBox->currentText() == "商品管理"){
        MainWindow *goods_control = new MainWindow("goods");  // 商品表名
        goods_control->show();
    }
    else if(ui->comboBox->currentText() == "订单管理"){
        MainWindow *orders_control = new MainWindow("orders");
        orders_control->show();
    }
    this->close();
}


void choseTableDialog::on_pushButton_2_clicked()
{
    LoginDialog *login = new LoginDialog;
    this->close();
    login->show();
}

