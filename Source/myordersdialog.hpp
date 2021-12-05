#ifndef MYORDERSDIALOG_HPP
#define MYORDERSDIALOG_HPP

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>

namespace Ui {
class myOrdersDialog;
}

class myOrdersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit myOrdersDialog(QWidget *parent = nullptr);
    ~myOrdersDialog();

private:
    Ui::myOrdersDialog *ui;
    QSqlDatabase db;
    QSqlQueryModel model;
    void createDB();
};

#endif // MYORDERSDIALOG_HPP
