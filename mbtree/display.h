#ifndef DISPLAY_H
#define DISPLAY_H

#include <QDialog>

namespace Ui {
class display;
}

class display : public QDialog
{
    Q_OBJECT

public:
    explicit display(QWidget *parent = nullptr);
    ~display();

private slots:
    void on_display_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::display *ui;
};

#endif // DISPLAY_H
