#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "restaurant.h"


//function to add a group/new node to the restaurantQueue/linked list
void addToList(restaurantQueue **head, char *name, int size, status status)
{
    //create new node
    restaurantQueue *temp = (restaurantQueue*)malloc(sizeof(restaurantQueue));

    if(temp == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for new node\n");
        exit(-1);
    }

    temp->groupName = name;
    temp->groupSize = size;
    temp->next = NULL;

    if(status == onWaitList)
    {
        temp->status = onWaitList;
    }
    else
    {
        temp->status = called;
    }

    //check if list is empty, and add to front
    if(*head == NULL){
        *head = temp;
        (*head)->prev = NULL;
        //printf("added at beginning\n");
    }
    else
    {
        restaurantQueue *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = temp;
        temp->prev = current;
        //printf("not new list, added to the back\n");
        return;
    }
    return;
}//end addToList()

//function that checks if the name of the group to be added already exist on the list
int doesNameExist(restaurantQueue **head, char *name)
{
    restaurantQueue *current = *head;

    if(current == NULL)
    {
        return FALSE;
    }
    while (current != NULL)
    {
        if(strcmp(current->groupName, name) == 0)
        {
            return TRUE;
        }
        current = current->next;
    }
    return FALSE;
}//end doesNameExist()

//boolean function that updates the status of groups from called in - to onWaitList
boolean updateStatus(restaurantQueue **head, char *name, int debugMode)
{
    restaurantQueue *current = *head;

    //base case
    if(current == NULL)
    {
        printf("List is Empty\n");
        return FALSE;
    }

    while ((current != NULL))
    {
        if(debugMode == TRUE)
        {
            printf("Group Name: %s\t Group Size: %d\t Status: %d \n", current->groupName, current->groupSize, current->status);
        }
        if (strcmp(current->groupName, name) == 0)
        {
            if(current->status == onWaitList)
            {
                return FALSE;
            }
            else{
                current->status = onWaitList;
                return TRUE;
            }
        }
        current = current->next;
    }
    return FALSE;
}//end updateStatus

//function that finds the group to be removed from the restaurantQueue based on tableSize integer
void retrieveAndRemove(restaurantQueue **head, int tableSize, int debugMode)
{
    restaurantQueue *current = *head;

    //base case - list is empty
    if (current == NULL)
    {
        printf("There are no groups before you.\n");
        return;
    }

    //Checking the first node of the linked list
    if (current->groupSize <= tableSize &&  current->status == 0)
    {

        restaurantQueue *other = current;
        current = current->next;
        int queueCounter = 1;

        printf ("Group with name %s with size of %d was retrieved!\n", other->groupName, other->groupSize);

        free(other);
        *head = current;

        if(debugMode == TRUE)
        {
            displayListInformation(head, queueCounter);
        }
        return;
    }

    //checking the middle of the list
    while(current->next != NULL)
    {
        if(debugMode == TRUE)
        {
            printf("Group Name: %s\t Group Size: %d\t Status: %d \n", current->groupName, current->groupSize, current->status);
        }
        if (current->groupSize <= tableSize && current->status == 0)
        {
            current->next->prev = current->prev;
            current->prev->next = current->next;
            printf ("Group with name %s with size of %d was retrieved!\n", current->groupName, current->groupSize);
            //free(current->groupName);
            free (current);
            //head = current;
            return;
        }
        current = current->next;
    }

    //checking last node of the list
    if (current->groupSize <= tableSize && current->status == 0)
    {
        current->prev->next = NULL;
        printf ("Group with name %s with size of %d was retrieved!\n", current->groupName, current->groupSize);
        free (current);
        return;
    }
    printf ("Error: Table size not found!\n");
}//end retrieveAndRemove()

//recursive function that counts and returns the group's size ahead of the one specified by name
int countGroupsAhead(restaurantQueue **head, char *name, int groupsCounter)
{
    restaurantQueue *current = *head;

    // Base case
    if (current == NULL)
    {
        return 0;
    }

    if (strcmp(current->groupName, name) == 0)
    {
        return 1;
    }

    if((strcmp(current->groupName, name) != 0))
    {
        printf("%d: Group of size %d.\n", groupsCounter, current->groupSize);
        (groupsCounter)++;
    }
    return countGroupsAhead(&current->next, name, groupsCounter);
}//end countGroupsAhead()

//funciton that works with countGroupsAhead to print the groups ahead
void displayGroupSizeAhead(restaurantQueue **head, char *name, int groupsCounter)
{
    countGroupsAhead(head, name, groupsCounter);

}//end displayGroupSizeAhead()

//recursive funciton that prints out the whole list/restaurantQueue
void displayListInformation(restaurantQueue **head, int queueCounter)
{
    (queueCounter)++;
    restaurantQueue *current = *head;

    //base case
    if (current == NULL)
    {
        printf("Queue list is empty!\n");
        return;
    }
    printf("%d: Group Size: %d\t Group Name: %s\t Status: ", queueCounter, current->groupSize, current->groupName);
    if(current->status == 0)
    {
        printf("Waiting in restaurant.\n");
    }
    else{
        printf("Called the restaurant.\n");
    }
    if (current->next == NULL)
    {
        return;
    }

    //recursive call
    displayListInformation(&current->next, queueCounter);
}//end displayListInformation()

//function to clear memory used by malloc.
void freeMemory(restaurantQueue **head)
{
    restaurantQueue* iter = *head;
    while(iter != NULL)
    {
        iter = iter->next;
        free(*head);
        *head = iter;
    }
}//end freeMemory()
