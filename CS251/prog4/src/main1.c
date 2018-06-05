#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

/* TEST CASE 1 */
int main(int argc, char** argv)
{
        int capacity;
        printf("Enter Capacity: ");
        scanf("%d", &capacity);

        PQ* pq = pq_create(capacity, 0);

        //printf("\nEnter Value: ");
        for(int i = 0; i < capacity; i++)
        {
                int temp;
                printf("\n-----------------------------------------------------------------------------------------\n");
                printf("\nEnter Value: ");
                scanf("%d", &temp);
                pq_insert(pq, i, temp);
                printHeap(pq);
                printPriorities(pq);
        }
        
           //delete all
           for(int i = 0; i < capacity; i++)
           {
                pq_remove_by_id(pq, i);              //REMOVE THIS LOOP OUT AND SEE IF IT IS WORKING FIRSTS
                printHeap(pq);
                printPriorities(pq);
           }


        return 0;


        int t1;
        double t2;
        for(int i = 0; i < capacity; i++)
        {
                printf("\n-----------------------------------------------------------------------------------------\n");
                if(pq_delete_top(pq, &t1, &t2) == 1)
                        printf("\ndelete top, id = %d, priority = %f\n", t1, t2);
                //printHeap(pq);
                //printPriorities(pq);
        }

        //change priority 1
        printf("change priority 1\n");
        pq_change_priority(pq, 1, 300);
        //printHeap(pq);
        printPriorities(pq);

        int temp1;
        double temp2;

        //delete top 1
        printf("delete top 1\n");
        if(pq_delete_top(pq, &temp1, &temp2) == 1)
                printf("delete top, id = %d, priority = %f\n", temp1, temp2);
        printHeap(pq);
        printPriorities(pq);

        //delete top 2
        printf("delete top 2\n");
        if(pq_delete_top(pq, &temp1, &temp2) == 1)
                printf("delete top, id = %d, priority = %f\n", temp1, temp2);
        printHeap(pq);
        printPriorities(pq);

        //insert 1
        printf("insert 1\n");
        pq_insert(pq, 2, 20);
        printHeap(pq);
        printPriorities(pq);

        //insert 2
        printf("insert 2\n");
        pq_insert(pq, 1, 100);
        printHeap(pq);
        printPriorities(pq);

        pq_free(pq);
        return 0;
}
