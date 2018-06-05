#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "myListNode.h"

MyListNode::MyListNode (int v1)
{
        this->elem = v1;
        this->next = NULL;
}

MyListNode::MyListNode (int v1, MyListNode* n)
{
        this->elem = v1;
        this->next = n;
}

void MyListNode::setElem (int e)
{
        this->elem = e;
}

int MyListNode::getElem ()
{
        return this->elem;
}

void MyListNode::setNext (MyListNode* n)
{
        this->next = n;
}

MyListNode* MyListNode::getNext()
{
        return this->next;
}
