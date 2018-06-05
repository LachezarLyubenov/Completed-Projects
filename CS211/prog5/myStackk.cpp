#include <cstdio>
#include <cstring>
#include <cctype>

#include "myStack.h"


myStack::myStack ( )
{
        allocatedSize = 2;
        this->arrayPtr = new int [ this->allocatedSize ];
        used = 0;
}

myStack::~myStack()
{
        delete[] arrayPtr;
}
void myStack::reset ()
{
        allocatedSize = 2;
        used = 0;
}

void myStack::push ( int val)
{
        if ( allocatedSize <= used )
        {
                int* tmp = new int [allocatedSize + 2];
                int a;
                for ( a = 0; a < used; a++)
                {
                        tmp[a] = arrayPtr[a];
                }
                delete [] arrayPtr;
                arrayPtr = tmp;
                allocatedSize = allocatedSize + 2;
        }
        arrayPtr[used] = val;
        used++;
}

void myStack::pop (int val)
{
        if(!isEmpty())
        {
                //printf("Stack is not empty . Remove element.");
                used--;
        }
}

int myStack::top ()
{
        if (isEmpty())
        {
                return -9999;
        }

        return arrayPtr[used-1];
}

bool myStack::isEmpty ()
{
        return used == 0;
}
