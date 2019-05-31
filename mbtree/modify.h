#ifndef MODIFY_H
#define MODIFY_H

#include <QDialog>

namespace Ui {
class modify;
}

class modify : public QDialog
{
    Q_OBJECT

public:
    explicit modify(QWidget *parent = nullptr);
    ~modify();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::modify *ui;
};

#endif // MODIFY_H
