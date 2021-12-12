#ifndef MENUWIDGET_HPP
#define MENUWIDGET_HPP

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class MenuWidget; }
QT_END_NAMESPACE

class MenuWidget : public QWidget
{
    Q_OBJECT

public:
    MenuWidget(QWidget *parent = nullptr);
    ~MenuWidget();
    void createDB();
    void createTable();
    void queryTable();      // 显示所有商品数据

private slots:
    void on_myOrderButton_clicked();

    void on_releaseButton_clicked();

    void on_myinfoButton_clicked();

    void on_buyButton_clicked();

    void on_orderButton_clicked();

    void on_searchButton_clicked();

    void on_RenewpushButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MenuWidget *ui;
    QSqlDatabase db;
    QSqlQueryModel model;
private:
    void initTable();
};
#endif // MENUWIDGET_HPP
