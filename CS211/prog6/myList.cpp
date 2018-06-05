#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "myList.h"


MyList::MyList()
{
        this->head = NULL;
        this->listSize = 0;
}

MyList::~MyList()
{
        MyList::~MyList();
}

void MyList::show()
{
        MyListNode* temp = head;

        if (temp == NULL)
        {
                printf("Nothing to print - list is empty\n");
        }
        while (temp != NULL )
        {
                printf("Elements: %d", temp->getElem());
                temp = temp->getNext();
        }
        printf("\n");
}

void MyList::insert (int x)
{
        MyListNode* temp = new MyListNode (x);

        // this code just inserts the node at the beginning of the list
        temp->setNext (head);
        head = temp;

}

void MyList::remove (int v1)
{
        MyListNode* temp = head;
        MyListNode* temp2 = temp;

        if (temp == NULL)
        {
                printf("Cannot delete, list is empty!\n");
        }

        if (head->getElem() == v1)
        {
                head = head->getNext();
        }

        while(temp->getNext() != NULL)
        {
                if(temp->getElem() == v1)
                {
                        temp2= temp->getNext();
                        temp = NULL;
                        return;
                }
                temp2 = temp;
                temp = temp->getNext();
        }
        if (temp->getElem() == v1)
        {
                temp2 = NULL;
                return;
        }
}
