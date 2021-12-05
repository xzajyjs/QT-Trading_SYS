#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QGroupBox>
#include <QSqlTableModel>
#include <QTableView>
#include <QListWidget>
#include <QLineEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString &commodityTable, QWidget *parent = 0);
    ~MainWindow();

private slots://槽函数
    void changeComView(QModelIndex index);//定位选择的行，并在右边list中显示出来
    void removeComFromComModel();//删除记录
    void searchSlot();//按name查找
    void returnSlot();//返回列表
    void addNewSlot();//添加按钮，创建添加记录的对话框
    void quitBtnSlot();//退出程序

private:
    QGroupBox *createComGroup();
    QGroupBox *createDetailGroup();
    QSqlTableModel *comModel;
    QTableView *comView;
    QListWidget *showList;
    QListWidgetItem *item;

    QLineEdit *seLineEdit;
    QLineEdit *se1LineEdit;
    QLineEdit *idLineEdit;
    QLineEdit *categoryLineEdit;
    QLineEdit *nameLineEdit;
    QLineEdit *noticeLineEdit;
    QLineEdit *priceLineEdit;
};

#endif // MAINWINDOW_H
