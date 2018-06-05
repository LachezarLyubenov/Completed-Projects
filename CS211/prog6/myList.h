#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "myListNode.h"

#ifndef MYLIST_H
#define MYLIST_H

class MyList
{
private:
// Create the Data Members for the MyList class here
MyListNode* head;
int listSize;

public:
MyList();
~MyList();
void show();
void insert (int x);
void remove (int v1);

};

#endif
