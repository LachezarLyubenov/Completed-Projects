#pragma once

#include <cstdio>
#include <cstring>
#include <cstdlib>


class MyListNode
{
private:
// Create the Data Members for the MyNode class here
int elem;
MyListNode* next;

public:
MyListNode (int v1);
MyListNode (int v1, MyListNode* n);
~MyListNode();

void setElem (int e);
int getElem ();
void setNext (MyListNode* n);
MyListNode* getNext();
};
