#include "insert.h"
#include "ui_insert.h"
#include <QMessageBox>
#include "btree.h"
#include<iostream>
#include<sstream>

insert::insert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::insert)
{
    ui->setupUi(this);
}

insert::~insert()
{
    delete ui;
}

void insert::on_insert_2_clicked()
{   person p;
    btree b;
    getvalues value;
    int key;
    fstream file2,file3;
    delimtextbuffer buff;
    char filename[20]="name.txt";
    operations o(filename);
    file3.open("rr.txt",ios::in);
    if(!file3.fail())
    {
        ifstream infile("rr.txt");
        int byteid,byteoffset;
        while(infile>>byteid>>byteoffset)
        {
            b.insert(byteid,byteoffset);
        }
    }
    QString id1=ui->l1->text();
    QString name1=ui->l2->text();
    QString address1=ui->l3->text();
    QString disease1=ui->l4->text();
    QString doctor1=ui->l5->text();
    char id[20],name[20],address[20],disease[20],doctor[20];
    string id2=id1.toStdString();
    string name2=name1.toStdString();
    string address2=address1.toStdString();
    string disease2=disease1.toStdString();
    string doctor2=doctor1.toStdString();
    strcpy(id,id2.c_str());
    strcpy(name,name2.c_str());
    strcpy(address,address2.c_str());
    strcpy(disease,disease2.c_str());
    strcpy(doctor,doctor2.c_str());
    strcpy(p.id,id);
    strcpy(p.name,name);
    strcpy(p.address,address);
    strcpy(p.disease,disease);
    strcpy(p.doctor,doctor);
    value=o.insert(p);
    stringstream geek(value.idn);
    key=0;
    geek>>key;
    b.insert(key,value.offsett);
    if(a==0){
        buff.pack(p);
        fstream os(filename, ios::out | ios::app);
        os.write(buff.buffer, strlen(buff.buffer));
        file2.open("rr.txt", ios::out | ios::app);
        file2 << value.idn << " " << value.offsett << endl;
        os.close();
        file2.close();
        QMessageBox::about(this,"INSERT","Record Inserted!!");
    }
    else if(a==1){
         cout<<"WONT BE ADDED";
         QMessageBox::about(this,"INSERT","Duplicate Record!!");
    }
    file3.close();
}

void insert::on_pushButton_2_clicked()
{
    ui->l1->clear();
    ui->l2->clear();
    ui->l3->clear();
    ui->l4->clear();
    ui->l5->clear();
}

void insert::on_pushButton_clicked()
{
    close();
}
