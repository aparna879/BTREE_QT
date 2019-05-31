#include<iostream>
#include<stdio.h>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<sstream>
#include<ctype.h>
#include<bits/stdc++.h>
using namespace std;

class delimtextbuffer;
class person
{
public:
	char id[20];
	char name[18];
	char address[20];
	char disease[20];
	char doctor[20];

	void input();
	void output();
	friend class delimtextbuffer;
};
class delimtextbuffer
{
	char buffer[160];
	char delim;
	public:
		void pack(person& p);
		int unpack(person& p);
		void Read(fstream& fs);
		int Write(char *filename);
		delimtextbuffer();
};

struct getvalues {
string idn;
int offsett;
};

class operations
{
	char *recordfilename;
public:
	operations(char *recordfile);
	void search(int offset);
	getvalues insert();
};

operations::operations(char *recordfile)
{
	recordfilename=recordfile;
}

void person::input()
{   char x;
	cout<<"Enter id"<<endl;
	//flush();
	cin.getline(id,20,'\n');
	cin.getline(id,20,'\n');
	cout<<"Enter name"<<endl;
	cin.getline(name,20,'\n');

	cout<<"Enter address"<<endl;
	cin.getline(address,20,'\n');

	cout<<"Enter disease"<<endl;
	cin.getline(disease,20,'\n');

	cout<<"Enter doctor"<<endl;
	cin.getline(doctor,20,'\n');

}

void person::output()
{
	cout<<"id:";
	puts(id);
	cout<<"Name:";
	puts(name);
	cout<<"Address:";
	puts(address);
	cout<<"disease:";
	puts(disease);
	cout<<"doctor:";
	puts(doctor);
}

delimtextbuffer::delimtextbuffer()
{
	for(int i=0;i<160;i++)
		buffer[i]='\0';
	    delim='|';
}

void delimtextbuffer::pack(person &p)
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
	strcat(buffer,"*");
}

int delimtextbuffer::unpack(person &p)
{
	char *ptr=buffer;

	while(*ptr)
	{
		if(*ptr == '|')
			*ptr = '\0';
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

void delimtextbuffer::Read(fstream& fs)
{
	fs.getline(buffer,160,'*');
}

int delimtextbuffer::Write(char *filename)
{
	fstream os(filename,ios::out|ios::app);
	os.seekg(0,ios::end);
	int offset=os.tellp();
	os.write(buffer,strlen(buffer));
	os.close();
	return offset;
}

void operations::search(int offset)
{
	delimtextbuffer buff;
	person p;
	fstream file1(recordfilename,ios::in);
	file1.seekg(offset,ios::beg);
	buff.Read(file1);
	buff.unpack(p);
	p.output();
	file1.close();
}

getvalues operations::insert()
{
	getvalues g;
	person ob;
	delimtextbuffer buff;
	int offset;
	fstream file,file2;
	ob.input();
	string x(ob.id);
	g.idn=x;
	buff.pack(ob);
	offset=buff.Write(recordfilename);
	g.offsett=offset;
	file2.open("rr.txt",ios::out|ios::app);
	file2<<g.idn<<" "<<g.offsett<<endl;
	return g;
}

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

node :: node()
{
	for(int i = 0; i < 4; i++)
	{
		next[i] = NULL;
		addr[i]=NULL;
	}
	parent = NULL;
	size = 0;
}

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
		void traversed(node *ptr);
		btree();
};

void btree :: traverse(node *ptr)
{
	if(ptr == NULL)
		return;
	for(int i = 0; i < ptr->size; i++)
		cout<<ptr->a[i]<<" ";
	cout<<endl;
	for(int i = 0; i < ptr->size;i++)
		traverse(ptr->next[i]);
}

void btree :: traversed(node *ptr)
{
	operations o("name.txt");
	if(ptr == NULL)
		return;
	for(int i = 0; i < ptr->size; i++){
		if(ptr->next[i]==NULL)
			o.search(ptr->addr[i]);
	}
	cout<<endl;
	for(int i = 0; i < ptr->size;i++)
		traversed(ptr->next[i]);
}

btree :: btree()
{
	root = NULL;
}

node* btree :: findLeaf(int key,int &level)
{
	node *ptr = root;
	node *prevptr = NULL;
	level = 0;
	int i;
	while(ptr)
	{
		i = 0;
		level++;
		while(i < ptr -> size-1 && key>ptr -> a[i])
				i++;
		prevptr = ptr;
		ptr = ptr -> next[i];
	}
	return prevptr;
}

node* btree :: split(node *n)
{
	int midpoint = (n -> size+1)/2;
	int newsize = n->size - midpoint;
	node *newptr = new node;
	node *child;
	newptr->parent = n -> parent;
	int i;
	for(i = 0; i < midpoint; i++)
	{
		newptr->a[i] = n->a[i];
		newptr->next[i] = n->next[i];
		newptr->addr[i]=n->addr[i];
		n->a[i] = n->a[i+midpoint];
		n->next[i] = n->next[i+midpoint];
		n->addr[i]=n->addr[i+midpoint];
	}
	n->size = midpoint;
	newptr -> size = newsize;
	for( i = 0; i < n->size; i++)
	{
		child = n->next[i];
		if(child!= NULL)
			child -> parent = n;
	}
	for( i = 0; i < newptr -> size; i++)
	{
		child = newptr -> next[i];
		if(child!= NULL)
			child -> parent = newptr;
	}
	return newptr;
}

void btree :: updateKey(node *parent,node *child,int newkey)
{
	if( parent == NULL)
		return;
	if(parent->size == 0)
		return;
	int oldkey = child->a[child->size-2];
	for(int i = 0; i < parent->size;i++)
	if(parent->a[i]==oldkey)
	{
		parent->a[i] = newkey;
		parent->next[i] = child;
	}
}
void btree :: insertIntoNode(node *n,int key,int offset,node *address)
{
	int i;
	if( n == NULL)
		return;
	for(i = 0; i < n->size; i++)
		if(n->a[i] == key)
			return;
	i = n->size-1;
    while(i >= 0 && n -> a[i] > key)
	{
		n->a[i+1] = n->a[i];
		n->next[i+1] = n->next[i];
		n->addr[i+1]=n->addr[i];
		i--;
	}
	i++;
	n->a[i] = key;
	n->next[i] = address;
	n->addr[i]=offset;
	n->size++;
	if( i == n->size-1)
		updateKey(n->parent,n,key);
}

void btree :: promote(node *n,int key,int offset,node *address)
{
	if( n == NULL)
		return;
	if(n -> size < 4)
	{
		insertIntoNode(n,key,offset,address);
		return;
	}
	if( n == root)
	{
		root = new node;
		n->parent = root;
	}
	node *newptr = split(n);
	node *t;
	if(key < n->a[0])
		t = newptr;
	else
		t = n;
	insertIntoNode(t,key,offset,address);
	promote(n->parent,n->a[n->size-1],offset,n);
	promote(newptr->parent,newptr->a[newptr->size-1],offset,newptr);
}

void btree :: insert(int key,int offset)
{
	if( root == NULL)
	{
		root = new node;
		root->a[root->size] = key;
		root->addr[root->size]=offset;
		root->size++;
		return;
	}
	int level;
	node *leaf = findLeaf(key,level);
	int i;
	for(i = 0; i < leaf->size; i++){
		//cout<<"leaf"<<leaf->a[i]<<endl<<"key"<<key<<endl;
		if(leaf -> a[i] == key)
		{
			cout<<"The Key to be inserted already exists"<<endl;
			return;
		}
	}
	promote(leaf,key,offset,NULL);
	cout<<"---------------\n";
	traverse(root);
	cout<<"----------------\n";
}

int btree :: search(int key)
{
	person p;
	delimtextbuffer buff;
	if(root == NULL){
		cout<<"The tree Does not exist"<<endl;
	return 0;
	}
	int level;
	node *leaf = findLeaf(key,level);
	int flag = 0;
	for(int i = 0; i < leaf ->size; i++)
		if(leaf->a[i] == key)
		{
			flag = 1;
			cout<<"The Key "<<key<<" Exists in the B-Tree at the level"<<level<<"and offset is"<<leaf->addr[i]<<endl;
			return leaf->addr[i];
		}
	if(!flag)
		cout<<"The Key Searched for was not found"<<endl;
}

int main()
{
	btree b;
	int count=0;
	getvalues value;
	int choice = 1,key,offset;
	fstream file,file1,file2,file3;
	person ob;
	delimtextbuffer buff;
	char filename[20]="name.txt";
	operations o(filename);
	file3.open("rr.txt",ios::in);
	if(!file3.fail())
	{
		ifstream infile("rr.txt");
		int byteid,byteoffset;
		while(infile >> byteid >> byteoffset)
		{
			b.insert(byteid,byteoffset);
			count++;
		}
	}
	while(choice <=5)
	{
		cout<<"1.Insert a Key\n";
		cout<<"2.Search a key\n";
		cout<<"3.Display\n";
 		cout<<"4.Remove\n";
		cout<<"5.Exit\n";
		cin>>choice;
		switch(choice)
		{
			case 1:
			{
				cout<<"Enter The Key to be inserted in B-Tree\n";
				value=o.insert();
				//cout<<value.idn<<endl;
				//cout<<value.offsett<<endl;
				stringstream geek(value.idn);
				int key=0;
				geek>>key;
				//cout<<key;
				b.insert(key,value.offsett);
				count++;
			}
			break;

			case 2:
			{
				cout<<"Enter The key to be searched\n";
				cin>>key;
				int off=b.search(key);
				o.search(off);
			}
			break;

			case 3:cout<<"Display file contents"<<endl;
        		   b.traversed(b.root);
        		   break;

			case 4:remove("name.txt");
        		remove("rr.txt");
        		break;
			case 5: break;
		}
	}
	return 0;
}
