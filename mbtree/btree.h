#ifndef BTREE_H
#define BTREE_H
#include<iostream>
#include<stdio.h>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<sstream>
#include<ctype.h>
#include<bits/stdc++.h>
#include <QApplication>
#include <QAbstractTableModel>
using namespace std;

extern int a;
class delimtextbuffer;
class person
{public:
    char id[20];
    char name[20];
    char address[20];
    char disease[20];
    char doctor[20];

    //void input();
    //void output();
    friend class delimtextbuffer;
};
class delimtextbuffer
{
public:
    char buffer[160];
    char delim;
    void pack(person& p);
    void unpack(person& p);
    void Read(fstream& fs);
    int Write(char const* filename);
    delimtextbuffer();
};
struct getvalues {
    string idn;
    int offsett;
};
struct searchqt{
    char u[20];
    char n[20];
    char a[20];
    char b[20];
    char c[20];

};

class operations
{

    char const *recordfilename;

public:

    operations(char const *recordfile);
    searchqt search(int offset);
    getvalues insert(person& p);
};

class node
{
public:
int a[4];
node * next[4];
node * parent;
int addr[4];
int size;
node();
};

class btree
{
public:
node * root;
node* findLeaf(int key,int &level);
void updateKey(node *p,node *c,int newKey);
int search(int key);
void insert(int key,int offset);
void insertIntoNode(node *n,int key,int offset,node *address);
void promote(node *n,int key,int offset,node *address);
node* split(node *n);
void traverse(node *ptr);
//QList<searchqt> traversed(node *ptr);
btree();
friend class operations;
};

#endif // BTREE_H
