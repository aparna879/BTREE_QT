#include "search.h"
#include "ui_search.h"
#include "btree.h"
#include "QMessageBox"

search::search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::search)
{
    ui->setupUi(this);
}

search::~search()
{
    delete ui;
}

void search::on_search_2_clicked()
{
    searchqt s;
    btree b;
    int key;
    fstream file;
    delimtextbuffer buff;
    char filename[20]="name.txt";
    operations o(filename);
    file.open("rr.txt",ios::in);
    if(!file.fail())
    {
        ifstream infile("rr.txt");
        int byteusn,byteoffset;
        while(infile>>byteusn>>byteoffset)
        {
            b.insert(byteusn,byteoffset);
        }
    }
    QString key1=ui->lineEdit->text();
    key=key1.toInt();
    int off=b.search(key);
    s=o.search(off);
    if(off==-1){
       QMessageBox::about(this,"Search","RECORD DOESNOT EXISTS!!");
       return;
    }
    ui->lineEdit_2->insert(s.u);
    ui->lineEdit_3->insert(s.n);
    ui->lineEdit_4->insert(s.a);
    ui->lineEdit_5->insert(s.b);
    ui->lineEdit_6->insert(s.c);
}


void search::on_pushButton_clicked()
{
   ui->lineEdit_2->clear();
   ui->lineEdit_3->clear();
   ui->lineEdit_4->clear();
   ui->lineEdit_5->clear();
   ui->lineEdit_6->clear();
   ui->lineEdit->clear();
}

void search::on_pushButton_2_clicked()
{
    close();
}
