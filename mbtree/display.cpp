#include "display.h"
#include "ui_display.h"
#include "btree.h"
#include <QAbstractTableModel>
#include "QTableView"
#include "QMessageBox"

display::display(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::display)
{
    ui->setupUi(this);
}

display::~display()
{
    delete ui;
}

void display::on_display_2_clicked()
{
    searchqt data;
    operations o("name.txt");
    fstream file1("name.txt",ios::in);
    int byteid, byteoffset;
    ifstream infilee("rr.txt");
    ui->plainTextEdit->insertPlainText("ID\tNAME\tADDRESS   \t  DISEASE_NAME\t REF._DOCTOR");
    ui->plainTextEdit->insertPlainText("\n");
    while(infilee>>byteid>>byteoffset){
        file1.seekg(byteoffset,ios::beg);
        data=o.search(byteoffset);
        QString final;
        final.append(data.u);
        final.append("\t");
        final.append(data.n);
        final.append("\t");
        final.append(data.a);
        final.append("\t  ");
        final.append(data.b);
        final.append("\t");
        final.append(data.c);
        final.append("\n");
        ui->plainTextEdit->appendPlainText(final);
    }

}
void display::on_pushButton_clicked()
{
    close();
}
