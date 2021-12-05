#ifndef BUYGOODSDIALOG_HPP
#define BUYGOODSDIALOG_HPP

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class buyGoodsDialog;
}

class buyGoodsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit buyGoodsDialog(QWidget *parent = nullptr);
    ~buyGoodsDialog();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::buyGoodsDialog *ui;
    QSqlDatabase db;
    void createDB();
    void createTable();
};

#endif // BUYGOODSDIALOG_HPP
