#ifndef RELEASEGOODSDIALOG_HPP
#define RELEASEGOODSDIALOG_HPP

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QValidator>

namespace Ui {
class ReleaseGoodsDialog;
}

class ReleaseGoodsDialog : public QDialog
{
    Q_OBJECT

public:
    //explicit ReleaseGoodsDialog(QWidget *parent = nullptr);
    ReleaseGoodsDialog(const QString &from, QWidget *parent = nullptr);
    ~ReleaseGoodsDialog();

private slots:
    void on_releaseButton_clicked();

    void on_cancelButton_clicked();

signals:
    void order();

private:
    Ui::ReleaseGoodsDialog *ui;
    void createDB();
    QSqlDatabase db;
};

#endif // RELEASEGOODSDIALOG_HPP
