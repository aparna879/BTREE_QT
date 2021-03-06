#include "modify.h"
#include "ui_modify.h"
#include "btree.h"
#include "QMessageBox"

modify::modify(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify)
{
    ui->setupUi(this);
}

modify::~modify()
{
    delete ui;
}

void modify::on_pushButton_clicked()
{
    searchqt s;
    btree b;
    person p;
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
    QString pname=ui->lineEdit->text();
    QString paddress=ui->lineEdit->text();
    QString pdisease=ui->lineEdit->text();
    QString pdoctor=ui->lineEdit->text();
    key=key1.toInt();
    std::string name=pname.toStdString();
    std::string address=paddress.toStdString();
    std::string disease=pdisease.toStdString();
    std::string doctor=pdoctor.toStdString();
    int off=b.search(key);
    s=o.search(off);
    strcpy(p.id,s.u);
    strcpy(p.name,s.n);
    strcpy(p.address,s.a);
    strcpy(p.disease,s.b);
    strcpy(p.doctor,s.c);
    strcpy(p.name,name.c_str());
    strcpy(p.address,address.c_str());
    strcpy(p.disease,disease.c_str());
    strcpy(p.doctor,doctor.c_str());
    QMessageBox::about(this,"Search","RECORD MODIFIED!!");
    if(off==-1){
       QMessageBox::about(this,"Search","RECORD DOESNOT EXISTS!!");
       return;
    }
//    ui->lineEdit_2->insert(s.u);
//    ui->lineEdit_3->insert(s.n);
//    ui->lineEdit_4->insert(s.a);
//    ui->lineEdit_5->insert(s.b);
//    ui->lineEdit_6->insert(s.c);
}

void modify::on_pushButton_2_clicked()
{

}

void modify::on_pushButton_3_clicked()
{
    close();
}
