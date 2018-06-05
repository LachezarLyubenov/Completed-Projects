#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

/* TEST CASE 2 */
int main(int argc, char** argv)
{
        int capacity;
        printf("Enter Capacity: ");
        scanf("%d", &capacity);

        PQ* pq = pq_create(capacity, 0);

        //time_t t;
        int randID;
        double randVal;
        //srand((unsigned) time(&t));
        srand((unsigned)time(NULL));
        for(int i = 0; i < capacity; i++)
        {
                randID = rand() % capacity;
                randVal = rand() % 1000;
                printf("\n-------------------------------------------------------------------------------\nInsert for id %d, priority = %f", randID, randVal);
                pq_insert(pq, randID, randVal);
                printHeap(pq);
                printPriorities(pq);
        }


        for(int i = 0; i < capacity; i++)
        {
                randID = rand() % capacity;
                printf("\n-------------------------------------------------------------------------------\nRemove for id %d", randID);
                pq_remove_by_id(pq, randID);
                printHeap(pq);
                printPriorities(pq);
        }

        for(int i = 0; i < capacity; i++)
        {
                randID = rand() % capacity;
                randVal = rand() % 1000;
                printf("\n-------------------------------------------------------------------------------\nInsert for id %d, priority = %f", randID, randVal);
                pq_insert(pq, randID, randVal);
                printHeap(pq);
                printPriorities(pq);
        }

        pq_free(pq);
        return 0;
}
