#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "restaurant.h"

//function that adds node based on correct input from restaurantMain as onWaitList or CallAhead
void doAdd(restaurantQueue **head, int debugMode)
{
    /* get group size from input */
    int size = getPosInt();
    if (size < 1)
    {
        printf ("Error: Add command requires an integer value of at least 1\n");
        printf ("Add command is of form: a <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }

    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Add command requires a name to be given\n");
        printf ("Add command is of form: a <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }

    int queueCounter = 1;
    int exists = doesNameExist(head, name);
    if (exists == 0)
    {
        if(debugMode == TRUE)
        {
            displayListInformation(head, queueCounter);
        }
        addToList(head, name, size, onWaitList);
        printf ("Adding In-restaurant group \"%s\" of size %d\n", name, size);
    }
    else{
        printf ("Error: This name is already on the restaurant list\n");
    }

}//end doAdd()

//function that lets user add groups to the restaurantQueue as a call ahead groups.
void doCallAhead (restaurantQueue **head, int debugMode)
{
    /* get group size from input */
    int size = getPosInt();
    if (size < 1)
    {
        printf ("Error: Call-ahead command requires an integer value of at least 1\n");
        printf ("Call-ahead command is of form: c <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }

    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Call-ahead command requires a name to be given\n");
        printf ("Call-ahead command is of form: c <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }

    //error checking and addition to the linked list
    int exists = doesNameExist(head, name);
    int queueCounter = 1;
    if (exists == 0)
    {
        if(debugMode == TRUE)
        {
            displayListInformation(head, queueCounter);
        }
        addToList(head, name, size, called);
        printf ("Adding Call-ahead group \"%s\" of size %d\n", name, size);
    }
    else{
        printf ("Error: This name is already on the restaurant list\n");
    }
}//end doCallAhead()

//function that changes a given group from called to onWaitList in the restaurantQueue
void doWaiting (restaurantQueue **head, int debugMode)
{
    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Waiting command requires a name to be given\n");
        printf ("Waiting command is of form: w <name>\n");
        printf ("  where: <name> is the name of the group that is now waiting\n");
        return;
    }

    //base case - list is empty
    if (!doesNameExist(head, name))
    {
        printf ("Error: No such name on the list!\n");
        return;
    }

    //if updateStatus is true, proceed to change the reservation as in-restaurant
    if (updateStatus(head, name, debugMode) == TRUE)
    {
        updateStatus(head, name, debugMode);
        printf ("Call-ahead group \"%s\" is now waiting in the restaurant\n", name);
    }
    else{
        printf ("Error: This group has already been marked as in-restaurant reservation.\n");
    }
}//end doWaiting()

//function that removes a node/group from the linked list if correct input and checks are met
void doRetrieve (restaurantQueue **head, int debugMode)
{
    /* get table size from input */
    int size = getPosInt();
    if (size < 1)
    {
        printf ("Error: Retrieve command requires an integer value of at least 1\n");
        printf ("Retrieve command is of form: r <size>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        return;
    }
    clearToEoln();
    printf ("Retrieve (and remove) the first group that can fit at a table of size %d\n", size);
    retrieveAndRemove(head, size, debugMode);
    return;
}//end doRetrieve()

//function that lists the groups ahead of a given group
void doList (restaurantQueue **head)
{
    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: List command requires a name to be given\n");
        printf ("List command is of form: l <name>\n");
        printf ("  where: <name> is the name of the group to inquire about\n");
        return;
    }

    int groupsCounter = 1;
    if (!doesNameExist(head, name))
    {
        printf ("No such name on the list\n");
        return;
    }
    printf ("Group \"%s\" is behind the following groups: \n", name);

    int g;
    displayGroupSizeAhead (head, name, groupsCounter);
    if (groupsCounter < 1)
    {
        printf ("No groups ahead!\n");
    }

}//end doList()

//function that prints the whole restaurantQueue list with all the information
void doDisplay (restaurantQueue **head)
{
    clearToEoln();
    int queueCounter = 0;

    printf ("Display information about all groups:\n");

    displayListInformation(head, queueCounter);

}//end doDisplay()
