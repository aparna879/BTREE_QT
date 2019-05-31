#ifndef INSERT_H
#define INSERT_H

#include <QDialog>

namespace Ui {
class insert;
}

class insert : public QDialog
{
    Q_OBJECT

public:
    explicit insert(QWidget *parent = nullptr);
    ~insert();

private slots:
    void on_insert_2_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::insert *ui;
};

#endif // INSERT_H
