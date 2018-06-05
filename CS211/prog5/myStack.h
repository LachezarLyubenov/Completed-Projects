/*
 *
 * Date: 03/19/2018
 *
 * Author: Lachezar Lyubenov
 *
 */

#include <cstdio>
#include <cstring>
#include <cctype>

// Class to hold the Token information
class myStack
{
private:
int used;
int allocatedSize;
int* arrayPtr;

public:

myStack ( );
~myStack();
void init();
bool isEmpty ();
void push ( int val);
void pop (int val);
void reset ();
void display();
int top ();

};
