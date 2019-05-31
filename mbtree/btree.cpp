#include "btree.h"
#include<iostream>
#include<stdio.h>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<sstream>
#include<ctype.h>
#include<bits/stdc++.h>
#include "QMessageBox"

#include <QApplication>
using namespace std;
int a;
void delimtextbuffer::pack(person& p)
{
    strcpy(buffer, p.id);
	strcat(buffer, "|");
	strcat(buffer, p.name);
	strcat(buffer, "|");
	strcat(buffer, p.address);
	strcat(buffer, "|");
    strcat(buffer, p.disease);
	strcat(buffer, "|");
    strcat(buffer, p.doctor);
	strcat(buffer, "|");
	strcat(buffer, "*");
}
void delimtextbuffer::unpack(person& p)
{
	char* ptr = buffer;

	while (*ptr)
	{
		if (*ptr == '|')
			* ptr = '\0';
		ptr++;
	}
	ptr = buffer;
    strcpy(p.id, ptr);
	ptr += strlen(ptr) + 1;
	strcpy(p.name, ptr);
	ptr += strlen(ptr) + 1;
	strcpy(p.address, ptr);
	ptr += strlen(ptr) + 1;
    strcpy(p.disease, ptr);
	ptr += strlen(ptr) + 1;
    strcpy(p.doctor, ptr);
}
void delimtextbuffer::Read(fstream & fs)
{
	fs.getline(buffer, 160, '*');
}
int delimtextbuffer::Write(char const* filename)
{
	fstream os(filename, ios::out | ios::app);
	os.seekg(0, ios::end);
	int offset = os.tellp();
	os.close();
	return offset;
}
searchqt operations::search(int offset)
{
	searchqt s;
	delimtextbuffer buff;
	person p;
	fstream file1(recordfilename, ios::in);
	file1.seekg(offset, ios::beg);
	buff.Read(file1);
	buff.unpack(p);
    strcpy(s.u, p.id);
	strcpy(s.n, p.name);
	strcpy(s.a, p.address);
    strcpy(s.b, p.disease);
    strcpy(s.c, p.doctor);
	file1.close();
	return s;
}

getvalues operations::insert(person & ob)
{
	getvalues g;
	delimtextbuffer buff;
	int offset;
    string x(ob.id);
    g.idn = x;
    offset = buff.Write(recordfilename);
	g.offsett = offset;
	return g;
}
delimtextbuffer::delimtextbuffer()
{
	for (int i = 0; i < 160; i++)
		buffer[i] = '\0';
	delim = '|';
}
operations::operations(char const* recordfile)
{

	recordfilename = recordfile;
}

btree::btree()
{
    root = nullptr;
}
node::node()
{
	for (int i = 0; i < 4; i++)
        next[i] = nullptr;
    parent = nullptr;
	size = 0;
}
void btree::traverse(node * ptr)
{
    if (ptr == nullptr)
		return;
	for (int i = 0; i < ptr->size; i++)
		cout << ptr->a[i] << " ";
	cout << endl;
	for (int i = 0; i < ptr->size; i++)
		traverse(ptr->next[i]);
    return;
}

node* btree::findLeaf(int key, int& level)
{
	node* ptr = root;
    node* prevptr = nullptr;
	level = 0;
	int i;
	while (ptr)
	{
		i = 0;
		level++;
		while (i < ptr->size - 1 && key>ptr->a[i])
			i++;
		prevptr = ptr;
		ptr = ptr->next[i];
	}
	return prevptr;
}

node* btree::split(node * n)
{
    int midpoint = (n->size + 1) / 2;
    int newsize = n->size - midpoint;
	node * newptr = new node;
	node * child;
	newptr->parent = n->parent;
	int i;
    for (i = 0; i < midpoint; i++)
	{
		newptr->a[i] = n->a[i];
		newptr->next[i] = n->next[i];
		newptr->addr[i] = n->addr[i];
        n->a[i] = n->a[i + midpoint];
        n->next[i] = n->next[i + midpoint];
        n->addr[i] = n->addr[i + midpoint];
	}
    n->size = midpoint;
	newptr->size = newsize;
	for (i = 0; i < n->size; i++)
	{
		child = n->next[i];
        if (child != nullptr)
			child->parent = n;
	}
	for (i = 0; i < newptr->size; i++)
	{
		child = newptr->next[i];
        if (child != nullptr)
			child->parent = newptr;
	}
	return newptr;
}
void btree::updateKey(node * parent, node * child, int newkey)
{
    if (parent == nullptr)
		return;
	if (parent->size == 0)
		return;
	int oldkey = child->a[child->size - 2];
	for (int i = 0; i < parent->size; i++)
		if (parent->a[i] == oldkey)
		{
			parent->a[i] = newkey;
			parent->next[i] = child;
		}
}
void btree::insertIntoNode(node * n, int key, int offset, node * address)
{
	int i;
    if (n == nullptr)
		return;
	for (i = 0; i < n->size; i++)
		if (n->a[i] == key)
			return;
	i = n->size - 1;
	while (i >= 0 && n->a[i] > key)
	{
		n->a[i + 1] = n->a[i];
		n->next[i + 1] = n->next[i];
		n->addr[i + 1] = n->addr[i];
		i--;
	}
	i++;
	n->a[i] = key;
	n->next[i] = address;
	n->addr[i] = offset;
	n->size++;
	if (i == n->size - 1)
		updateKey(n->parent, n, key);
}
void btree::promote(node * n, int key, int offset, node * address)
{
    if (n == nullptr)
		return;
	if (n->size < 4)
	{
		insertIntoNode(n, key, offset, address);
		return;
	}
	if (n == root)
	{
		root = new node;
		n->parent = root;
	}
	node* newptr = split(n);
	node* t;
	if (key < n->a[0])
		t = newptr;
	else
		t = n;
	insertIntoNode(t, key, offset, address);
	promote(n->parent, n->a[n->size - 1], offset, n);
	promote(newptr->parent, newptr->a[newptr->size - 1], offset, newptr);
}

void btree::insert(int key, int offset)
{
    if (root == nullptr)
	{
		root = new node;
		root->a[root->size] = key;
		root->addr[root->size] = offset;
		root->size++;
		return;
	}
	int level;
	node* leaf = findLeaf(key, level);
	int i;
	for (i = 0; i < leaf->size; i++)
	{
		if (leaf->a[i] == key)
		{
			cout << "The Key to be inserted already exists" << endl;
            a=1;
            return;
		}
	}
    promote(leaf, key, offset, nullptr);
	cout << "---------------\n";
	traverse(root);
	cout << "----------------\n";

}

int btree::search(int key)
{
	delimtextbuffer buff;
    if (root == nullptr)
	{
		cout << "The tree Does not exist" << endl;
		return 0;
	}
	int level;
	node* leaf = findLeaf(key, level);
	int flag = 0;
	for (int i = 0; i < leaf->size; i++)
		if (leaf->a[i] == key)
		{

			flag = 1;
            cout << "The Key " << key << " Exists in the B-Tree at the level" << " "<<level <<" "<<"and offset is" <<" "<< leaf->addr[i] << endl;
			return leaf->addr[i];
		}
    if (!flag){
        cout << "The Key Searched was not found" << endl;
        return -1;
    }
    return 0;
}
