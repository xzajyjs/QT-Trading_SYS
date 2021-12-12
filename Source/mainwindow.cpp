#include "mainwindow.h"
#include "releasegoodsdialog.hpp"
#include "chosetabledialog.hpp"
#include <QGridLayout>
#include <QAbstractItemView>
#include <QPushButton>
#include <QSqlRecord>
#include <QMessageBox>
#include <QLabel>
#include <QtDebug>
#include <QSqlField>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

QString extern_commodity;
MainWindow::MainWindow(const QString &commodityTable, QWidget *parent):
    QMainWindow(parent)
{
    extern_commodity = commodityTable;
    qDebug() << "commodity = " << extern_commodity;
    QSqlError err;
    QSqlDatabase db = QSqlDatabase::addDatabase(("QSQLITE"));
    db.setDatabaseName("database.db");
    db.open();
    if(!db.open())
    {
        err = db.lastError();
        qDebug() << err.text();
    }
    //商品数据表模型
    comModel = new QSqlTableModel(this);
    comModel->setTable(commodityTable);
    comModel->select();

    QGroupBox *commodity = createComGroup();
    QGroupBox *detail = createDetailGroup();

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(commodity, 0, 0, 2, 1);
    layout->addWidget(detail, 0, 1, 2, 1);
    // 左侧商品框高与宽
    layout->setColumnMinimumWidth(0, 600);
    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
    resize(850, 400);
}

QGroupBox* MainWindow::createComGroup()//左边组合框
{
    comView = new QTableView;
    comView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置为不可编辑状态
    comView->setSortingEnabled(true);//开启排序
    comView->setSelectionBehavior(QAbstractItemView::SelectRows);//每次选择，选一行
    comView->setSelectionMode(QAbstractItemView::SingleSelection);//单击选择
    comView->setShowGrid(true);
    comView->setAlternatingRowColors(true);
    comView->setModel(comModel);
    connect(comView, SIGNAL(clicked(QModelIndex)), this, SLOT(changeComView(QModelIndex)));

    QString info;
    if(extern_commodity == "goods") info = "商品信息";
    else if(extern_commodity == "users") info = "用户信息";
    else if(extern_commodity == "orders") info = "订单信息";
    QGroupBox *box = new QGroupBox(info);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(comView, 0, 0);
    box->setLayout(layout);
    return box;
}

QGroupBox* MainWindow::createDetailGroup()//右边细节组合框
{
    QGroupBox *box = new QGroupBox(tr("细节"));
    showList = new QListWidget;

    QPushButton *deleteBtn = new QPushButton(tr("删除"));
    QPushButton *addBtn = new QPushButton(tr("添加商品"));
    QString info;
    if(extern_commodity == "goods") info = "通过名称查找";
    else if(extern_commodity == "users" || extern_commodity == "orders") info = "通过用户名查找";
    QPushButton *searchBtn = new QPushButton(info);
    QPushButton *returnBtn = new QPushButton(tr("重置"));
    QPushButton *quitBtn = new QPushButton(tr("返回"));

    connect(deleteBtn, SIGNAL(clicked(bool)), this, SLOT(removeComFromComModel()));
    connect(addBtn, SIGNAL(clicked(bool)), this, SLOT(addNewSlot()));
    connect(searchBtn, SIGNAL(clicked(bool)), this, SLOT(searchSlot()));
    connect(returnBtn, SIGNAL(clicked(bool)), this, SLOT(returnSlot()));
    connect(quitBtn, SIGNAL(clicked(bool)), this, SLOT(quitBtnSlot()));

    seLineEdit = new QLineEdit;
    se1LineEdit = new QLineEdit;
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(showList, 0, 0, 3, 2);
    layout->addWidget(deleteBtn, 3, 0, 1, 1);
    layout->addWidget(addBtn, 3, 1, 1, 1);
    layout->addWidget(seLineEdit, 4, 0, 1, 1);
    layout->addWidget(searchBtn, 4, 1, 1, 1);
    layout->addWidget(returnBtn, 6, 0, 1, 1);
    layout->addWidget(quitBtn, 6, 1, 1, 1);

    box->setLayout(layout);
    return box;
}
//当选中一行时，改变视图，右侧列表框显示详细信息
void MainWindow::changeComView(QModelIndex index)
{
    showList->clear();
    item = new QListWidgetItem(showList);
    QSqlRecord record = comModel->record(index.row());

    int comId = record.value("id").toInt();
    int BH = record.value("编号").toInt();
    QString name = record.value("名称").toString();
    int count = record.value("数量").toInt();
    double price = record.value("价格").toDouble();
    QString notice = record.value("备注").toString();

    int id = record.value("id").toInt();
    QString username = record.value("username").toString();
    QString password = record.value("password").toString();
    QString phone = record.value("phone").toString();
    QString address = record.value("address").toString();

    int order_id = record.value("id").toInt();
    int good_id = record.value("good_id").toInt();
    QString orders_username = record.value("username").toString();
    QString good_name = record.value("good_nae").toString();
    QString good_price = record.value("good_price").toString();
    QString good_number = record.value("good_number").toString();
    QString user_notice = record.value("user_notice").toString();

    QString info;
    if(extern_commodity == "goods"){
        item->setText(tr("ID: %1\n编号: %2\n名称: %3\n价格: %4\n数量: %5\n备注: %6\n").arg(comId).arg(BH).arg(name).arg(price).arg(count).arg(notice));
    }
    else if(extern_commodity == "users"){
        item->setText(tr("ID: %1\n用户名: %2\n密码: %3\n电话: %4\n地址: %5\n").arg(id).arg(username).arg(password).arg(phone).arg(address));
    }
    else if(extern_commodity == "orders"){
        item->setText(tr("ID: %1\n商品编号: %2\n买家昵称: %3\n商品名称: %4\n商品价格: %5\n商品数量: %6\n用户备注: %7\n").arg(order_id).arg(good_id).arg(orders_username).arg(good_name).arg(good_price).arg(good_number).arg(user_notice));
    }
}

void MainWindow::removeComFromComModel()
{
    QModelIndexList select = comView->selectionModel()->selectedRows();

    if(!select.empty())
    {
        QModelIndex idIndex = select.at(0);//得到选中行的id索引
        QString name = idIndex.sibling(idIndex.row(), 2).data().toString();
        QMessageBox::StandardButton button;
        button = QMessageBox::question(this,
                                       tr("删除"),
                                       QString(tr("确定删除 '%1' 吗?").arg(name)),
                                       QMessageBox::Yes|QMessageBox::No);
        if(button == QMessageBox::Yes)
        {
            comModel->removeRow(idIndex.row());
            comModel->submitAll();
            comModel->select();
        }
    }
}
//按查找
void MainWindow::searchSlot()
{
    QString name = seLineEdit->text();
    if(!name.isEmpty())
    {
        if(extern_commodity == "goods")
            comModel->setFilter(QObject::tr("名称 like '%%1%'").arg(name));
        else if(extern_commodity == "users")
            comModel->setFilter(QObject::tr("username like '%%1%'").arg(name));
        else if(extern_commodity == "orders")
            comModel->setFilter(QObject::tr("username like '%%1%'").arg(name));
        comModel->select();
        seLineEdit->clear();
    }
    else
        return;
}

void MainWindow::returnSlot()
{
    comModel->setTable(extern_commodity);
    comModel->setSort(0, Qt::AscendingOrder);
    comModel->select();
}

void MainWindow::addNewSlot()
{
    ReleaseGoodsDialog *release = new ReleaseGoodsDialog("admin");
    release->show();
    this->close();
}

void MainWindow::quitBtnSlot()
{
    choseTableDialog *choose = new choseTableDialog;
    choose->show();
    this->close();
}

MainWindow::~MainWindow()
{
    //delete ui;
}
