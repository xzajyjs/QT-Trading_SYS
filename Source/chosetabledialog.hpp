#ifndef CHOSETABLEDIALOG_HPP
#define CHOSETABLEDIALOG_HPP

#include <QDialog>

namespace Ui {
class choseTableDialog;
}

class choseTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit choseTableDialog(QWidget *parent = nullptr);
    ~choseTableDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::choseTableDialog *ui;
};

#endif // CHOSETABLEDIALOG_HPP
