#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include <string.h>

typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;
typedef enum {onWaitList = 0, called = 1} status;

//create a struct
typedef struct Node{
    char *groupName;
    int groupSize;
    status status;
    struct Node *next;
    struct Node *prev;
} restaurantQueue;

//restaurantMain functions:
int main(int argc, char **argv);
void clearToEoln();
int getNextNWSChar();
int getPosInt();
char *getName();
void printCommands();

//main helper functions:
void doAdd(restaurantQueue **head, int debugMode);
void doCallAhead(restaurantQueue **head, int debugMode);
void doWaiting(restaurantQueue **head, int debugMode);
void doRetrieve(restaurantQueue **head, int debugMode);
void doList (restaurantQueue **head);
void doDisplay(restaurantQueue **head);

//Linked list implementation functions:
void addToList(restaurantQueue **head, char *name, int size, status status);
int doesNameExist(restaurantQueue **head, char *name);
boolean updateStatus(restaurantQueue **head, char *name, int debugMode);
void retrieveAndRemove(restaurantQueue **head, int tableSize, int debugMode);
int countGroupsAhead(restaurantQueue **head, char *name, int groupsCounter);
void displayGroupSizeAhead(restaurantQueue **head, char *name, int groupsCounter);
void displayListInformation(restaurantQueue **head, int queueCounter);
void freeMemory(restaurantQueue **head);
