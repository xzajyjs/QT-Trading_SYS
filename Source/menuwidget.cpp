#include "menuwidget.hpp"
#include "ui_menuwidget.h"
#include "releasegoodsdialog.hpp"
#include "myprofiledialog.hpp"
#include "buygoodsdialog.hpp"
#include "myordersdialog.hpp"
#include "logindialog.hpp"

extern QString extern_username;
QString extern_phone;
QString extern_address;
int extern_id;

MenuWidget::MenuWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuWidget)
{
    ui->setupUi(this);
    ui->buyIdEdit->setValidator(new QIntValidator(this));
    initTable();
    createDB();
    createTable();
    queryTable();
    qDebug() << "外部用户名为：" << extern_username;
    ui->usernameLabel->setText(extern_username);

}

MenuWidget::~MenuWidget()
{
    delete ui;
}

// 美化表格
void MenuWidget::initTable(){
    ui->table->setAlternatingRowColors(true);
    // ......
}

// 创建数据库
void MenuWidget::createDB(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    if(db.open()){
        qDebug() << "数据库打开成功!";
    }
    else{
        qDebug() << db.lastError().text();
    }
    QString str;
    QSqlQuery query;
    str = QString("SELECT phone FROM users WHERE username='%1'").arg(extern_username);
    query.exec(str);query.next();
    extern_phone = query.value(0).toString(); //

    str = QString("SELECT address FROM users WHERE username='%1'").arg(extern_username);
    query.exec(str);query.next();
    extern_address = query.value(0).toString(); //

}

// 创建商品数据表
// id(INTEGER), 编号(INT), 名称(TEXT), 价格(DOUBLE), 数量(INT), 备注(TEXT),
void MenuWidget::createTable(){
    QString str = QString("CREATE TABLE goods("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                          "编号 INT NOT NULL,"
                          "名称 TEXT NOT NULL,"
                          "价格 DOUBLE NOT NULL,"
                          "数量 INT NOT NULL,"
                          "备注 TEXT);");
    QSqlQuery query;
    if(query.exec(str)){
        qDebug() << "数据表创建成功";
        query.exec("INSERT INTO goods(编号,名称,价格,数量,备注) "
                   "VALUES(12,'大学英语',25.5,1,'English for Chinese!')");
        query.exec("INSERT INTO goods(编号,名称,价格,数量,备注) "
                   "VALUES(5,'大学物理',50,2,'奇怪的角动量')");
        query.exec("INSERT INTO goods(编号,名称,价格,数量,备注) "
                   "VALUES(8,'安全带',19.9,12,'自行车上的安全带')");
        query.exec("INSERT INTO goods(编号,名称,价格,数量,备注) "
                   "VALUES(9,'高等数学I',35,1,'让高数带你走向人生的顶峰!')");
        query.exec("INSERT INTO goods(编号,名称,价格,数量,备注) "
                   "VALUES(1,'C++程序设计基础',59,1,'最最真宗的C++教程')");
        query.exec("INSERT INTO goods(编号,名称,价格,数量,备注) "
                   "VALUES(3,'数据结构',199,1,'通过插图带你走进数据结构的世界！')");
        query.exec("INSERT INTO goods(编号,名称,价格,数量,备注) "
                   "VALUES(7,'Java--从如图到入坟',89.5,1,'Java真的是世界上最牛逼的语言!doge')");
        query.exec("INSERT INTO goods(编号,名称,价格,数量,备注) "
                   "VALUES(22,'天堂牌雨伞',24,1,'不漏的伞')");
        query.exec("INSERT INTO goods(编号,名称,价格,数量,备注) "
                   "VALUES(32,'奥迪模型',399,1,'1:14比例')");
        query.exec("INSERT INTO goods(编号,名称,价格,数量,备注) "
                   "VALUES(10,'乐高战将',1999,1,'有点粗糙')");
        query.exec("INSERT INTO goods(编号,名称,价格,数量,备注) "
                   "VALUES(2,'iPhone13mini',5199,1,'128G国行')");
    }
    else{
        qDebug() << str;
    }
}
// 显示所有数据库信息
void MenuWidget::queryTable(){
    QString str = QString("SELECT 编号,名称,价格,数量,备注 FROM goods");
    model.setQuery(str);
    ui->table->setModel(&model);
}


// 我的订单
void MenuWidget::on_myOrderButton_clicked()
{
    myOrdersDialog *myOrders = new myOrdersDialog;
    myOrders->show();
}

// 发布商品
void MenuWidget::on_releaseButton_clicked()
{
    ReleaseGoodsDialog *release = new ReleaseGoodsDialog("user");
    release->show();
    this->close();
}

// 个人信息
void MenuWidget::on_myinfoButton_clicked()
{
    myProfileDialog *profile = new myProfileDialog;
    profile->show();
}

// 购买
void MenuWidget::on_buyButton_clicked()
{
    extern_id = ui->buyIdEdit->text().toInt();
    buyGoodsDialog *buy = new buyGoodsDialog;
    buy->show();
}

// 排序
void MenuWidget::on_orderButton_clicked()
{
    // 获得按什么排序
    QString value = ui->speciesComboBox->currentText();
    // 获取排序方式
    QString sort;
    if(ui->howComboBox->currentIndex() == 0){
        sort = QString("ASC");
    }
    else{
        sort = QString("DESC");
    }
    QString str = QString("SELECT 编号,名称,价格,数量,备注 FROM goods ORDER BY %1 %2").arg(value).arg(sort);
    model.setQuery(str);
    ui->table->setModel(&model);
}

// 查找
void MenuWidget::on_searchButton_clicked()
{
    QString search = QString("SELECT 编号,名称,价格,数量,备注 FROM goods "
                             "WHERE 名称='%1'").arg(ui->searchIdEdit->text());
    qDebug() << search;
    model.setQuery(search);
    ui->table->setModel(&model);
}


void MenuWidget::on_RenewpushButton_clicked()
{
    ui->searchIdEdit->setText("");
    queryTable();
}


void MenuWidget::on_pushButton_clicked()
{
    LoginDialog *login = new LoginDialog;
    this->close();
    login->show();
}

