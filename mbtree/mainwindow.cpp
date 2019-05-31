#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "insert.h"
#include "search.h"
#include "display.h"
#include "modify.h"
#include "QMessageBox"
#include <fstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    insert ins;
    ins.setModal(true);
    ins.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    search sea;
    sea.setModal(true);
    sea.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    display disp;
    disp.setModal(true);
    disp.exec();
}

void MainWindow::on_pushButton_4_clicked()

{
    std::fstream file;
    file.open("name.txt");
    if(!file.fail())
    {
    remove("name.txt");
    remove("rr.txt");
    QMessageBox::about(this,"Try","FILES DELETED!!");
    }
    else {
         QMessageBox::about(this,"Try","FILES DOES NOT EXIST");

    }
}

void MainWindow::on_pushButton_5_clicked()
{
    close();
}

