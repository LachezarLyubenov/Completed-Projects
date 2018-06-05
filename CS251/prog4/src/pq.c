#include "pq.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct idStruct {
  int position;
  int isThere; 
} idStruct;

typedef struct priorityStruct {
  double priority;
  int id;

} priorityStruct;

struct pq_struct {

  idStruct* arrayId;
  priorityStruct* arrayPri;
  int cap;
  int size;
  int minOrMax;

};


/**
* Function: pq_create
* Parameters: capacity - self-explanatory
*             min_heap - if 1 (really non-zero), then it is a min-heap
*                        if 0, then a max-heap
*                        
* Returns:  Pointer to empty priority queue with given capacity and
*           min/max behavior as specified.
*
*/
PQ * pq_create(int capacity, int min_heap)
{
  int counter;

  if(capacity <= 0)
  {
    return 0;
  }

  PQ *newHeap = malloc(sizeof(PQ));
  

	newHeap->arrayPri = (priorityStruct* )malloc(sizeof(priorityStruct) * (capacity + 1));
  newHeap->arrayPri[0].priority = -1;
  newHeap->arrayPri[0].id = -1;

  newHeap->arrayId =(idStruct* )malloc(sizeof(idStruct) * capacity);

  newHeap->size = 1;
  newHeap->cap = capacity;
  newHeap->minOrMax = min_heap;
  return newHeap;

}

/**
* Function: pq_free
* Parameters: PQ * pq
* Returns: --
* Desc: deallocates all memory associated with passed priority 
*       queue.
*
*/

void pq_free(PQ * pq)
{
  free(pq->arrayPri);
  free(pq->arrayId);
  free(pq);
}

/**
* Function: pq_insert
* Parameters: priority queue pq
*             id of entry to insert
*             priority of entry to insert
* Returns: 1 on success; 0 on failure.
*          fails if id is out of range or
*            there is already an entry for id
*          succeeds otherwise.
*          
* Desc: self-explanatory
*
* Runtime:  O(log n)
*
*/

void percUp(PQ * pq, int position)
{
  int parent = position/2;

  if (parent <= 0 )
  {
    return;
  }

  if (pq->minOrMax == 0) //max
  {
    if((pq->arrayPri[parent].priority < pq->arrayPri[position].priority) && (pq->arrayId[pq->arrayPri[parent].id].isThere == 1))
    {
      int currentID = pq->arrayPri[position].id;
      double currentPriority = pq->arrayPri[position].priority;
      //printf("\ncurrentID = %d, currentPriority = %f\n", currentID, currentPriority);

      int parentID = pq->arrayPri[parent].id;
      double parentPriority = pq->arrayPri[parent].priority;
      //printf("\nparentID = %d, parentPriority %f\n", parentID, parentPriority);
      pq->arrayPri[parent].priority = currentPriority;
      pq->arrayPri[position].priority = parentPriority;
      pq->arrayPri[position].id = parentID;
      pq->arrayPri[parent].id = currentID;
      pq->arrayId[currentID].position = parent;
      pq->arrayId[parentID].position = position;

      percUp(pq, parent);
    }
    else{
      return;
    }
  }
  else if (pq->minOrMax == 1) // min
  {
    if((pq->arrayPri[parent].priority > pq->arrayPri[position].priority) && (pq->arrayId[pq->arrayPri[parent].id].isThere == 1))
    {
      int currentID = pq->arrayPri[position].id;
      double currentPriority = pq->arrayPri[position].priority;
      //printf("\ncurrentID = %d, currentPriority = %f\n", currentID, currentPriority);

      int parentID = pq->arrayPri[parent].id;
      double parentPriority = pq->arrayPri[parent].priority;
      //printf("\nparentID = %d, parentPriority %f\n", parentID, parentPriority);
      pq->arrayPri[parent].priority = currentPriority;
      pq->arrayPri[position].priority = parentPriority;
      pq->arrayPri[position].id = parentID;
      pq->arrayPri[parent].id = currentID;
      pq->arrayId[currentID].position = parent;
      pq->arrayId[parentID].position = position;

      percUp(pq, parent);

    }
    else{
      return;
    }
  }
}

void percDown(PQ * pq, int position)
{
  if(2*position >= pq->size)
  {
    return;
  }
  int leftChild = 2*position;
  int rightChild = (2*position) + 1;
  int currentChild = 0;

  if ((leftChild <= 0 || rightChild <= 0) || (pq->size <= leftChild)) //|| pq->size <= rightChild)
  {
    return;
  }

  if (pq->minOrMax == 0)
  {
    if(pq->arrayPri[rightChild].priority > pq->arrayPri[leftChild].priority)
    {
      currentChild = rightChild;
    }
    else{
      currentChild = leftChild;
    }
    if((pq->arrayPri[currentChild].priority < pq->arrayPri[position].priority) && (pq->arrayId[pq->arrayPri[currentChild].id].isThere == 1))
    {
      int currentID = pq->arrayPri[position].id;
      int currentPriority = pq->arrayPri[position].priority;

      int childID = pq->arrayPri[currentChild].id;
      int childPriority = pq->arrayPri[currentChild].priority;

      pq->arrayPri[currentChild].priority = currentPriority;
      pq->arrayPri[position].priority = childPriority;
      pq->arrayPri[position].id = childID;
      pq->arrayPri[currentChild].id = currentID;
      pq->arrayId[currentID].position = currentChild;
      pq->arrayId[childID].position = position;

      percDown(pq, currentChild);
    }
    else{
      return;
    }
  }
  else if (pq->minOrMax == 1)
  {
    if(pq->arrayPri[rightChild].priority < pq->arrayPri[leftChild].priority)
    {
      currentChild = rightChild;
    }
    else{
      currentChild = leftChild;
    }

    if((pq->arrayPri[currentChild].priority > pq->arrayPri[position].priority) && (pq->arrayId[pq->arrayPri[currentChild].id].isThere == 1))
    {
      int currentID = pq->arrayPri[position].id;
      int currentPriority = pq->arrayPri[position].priority;

      int childID = pq->arrayPri[currentChild].id;
      int childPriority = pq->arrayPri[currentChild].priority;

      pq->arrayPri[currentChild].priority = currentPriority;
      pq->arrayPri[position].priority = childPriority;
      pq->arrayPri[position].id = childID;
      pq->arrayPri[currentChild].id = currentID;
      pq->arrayId[currentID].position = currentChild;
      pq->arrayId[childID].position = position;

      percDown(pq, currentChild);

    }
    else{
      return;
    }
  }
}

int pq_insert(PQ * pq, int id, double priority)
{
  if(pq->arrayId[id].isThere == 1)
  {
    return 0;
  }

  if (id >= pq->cap || id < 0)
  {
    return 0;
  }

  pq->arrayPri[pq->size].priority = priority;
  pq->arrayPri[pq->size].id = id;
  pq->arrayId[id].position = pq->size;
  //pq->arrayPri[id] = pq->arrayPri[pq->size];
  pq->arrayId[id].isThere = 1;


  percUp(pq, pq->size);
  //percDown(pq, pq->size);

  //printHeap(pq);
  pq->size++;

  return 1;
  
}

/**
* Function: pq_change_priority
* Parameters: priority queue ptr pq
*             element id
*             new_priority
* Returns: 1 on success; 0 on failure
* Desc: If there is an entry for the given id, its associated
*       priority is changed to new_priority and the data 
*       structure is modified accordingly.
*       Otherwise, it is a failure (id not in pq or out of range)
* Runtime:  O(log n)
*       
*/

int pq_change_priority(PQ * pq, int id, double new_priority)
{
    if(pq->arrayId[id].isThere == 0)
  {
    return 0;
  }

  if (id < 0 || id >= pq->cap)
  {
    return 0;
  }
        pq->arrayPri[pq->arrayId[id].position].priority = new_priority;
        percDown(pq, pq->arrayId[id].position);
        percUp(pq, pq->arrayId[id].position);
/*
    if(pq->minOrMax == 1)
    {
      if(pq->arrayPri[pq->arrayId[id].position].priority < new_priority)
      {
        pq->arrayPri[pq->arrayId[id].position].priority = new_priority;
        percDown(pq, pq->arrayId[id].position);
      }
      else{
        pq->arrayPri[pq->arrayId[id].position].priority = new_priority;
        percUp(pq, pq->arrayId[id].position);
      }
    }

    if(pq->minOrMax == 0)
    {
      if(pq->arrayPri[pq->arrayId[id].position].priority > new_priority)
      {
        pq->arrayPri[pq->arrayId[id].position].priority = new_priority;
        percDown(pq, pq->arrayId[id].position);
      }
      else{
        pq->arrayPri[pq->arrayId[id].position].priority = new_priority;
        percUp(pq, pq->arrayId[id].position);
      }
    }
    */
  return 1;
}


/**
* Function: pq_remove_by_id
* Parameters: priority queue pq, 
*             element id
* Returns: 1 on success; 0 on failure
* Desc: if there is an entry associated with the given id, it is
*       removed from the priority queue.
*       Otherwise the data structure is unchanged and 0 is returned.
* Runtime:  O(log n)
*
*/
int pq_remove_by_id(PQ * pq, int id)
{
  if(pq->arrayId[id].isThere == 0)
  {  
    //printf("Inside is there returns\n");
    //printf("id is: %d\n", id);

    return 0;
  }

  if (id < 0 || id > pq->cap+1)
  {
        //printf("Inside id statment returns\n");

    return 0;
  }

  //if(pq->arrayId[id].isThere == 1)
  //{
    int oldP = pq->arrayPri[pq->arrayId[id].position].priority;		
	  int newP = pq->arrayPri[pq->size-1].priority;

		int position = pq->arrayId[id].position;
/*
		if( position == pq->size-1)
    {
              printf("Inside position if returns\n");
      return 1;
    }
*/
		pq->arrayPri[position].priority = pq->arrayPri[pq->size-1].priority;
		pq->arrayPri[position].id = pq->arrayPri[pq->size-1].id;
		pq->arrayPri[pq->size-1].priority = 0;
		pq->arrayPri[pq->size-1].id = 0;
    //here?
    pq->arrayId[id].position = 0;
		pq->arrayId[pq->arrayPri[position].id].position = position;
		
		pq->arrayId[id].isThere = 0;
    
		percDown(pq, position);
		percUp(pq, position);

    //printHeap(pq);
	//}
  (pq->size)--;
	return 1;
}

/**
* Function: pq_get_priority
* Parameters: priority queue pq
*             elment id
*             double pointer priority ("out" param)
* Returns: 1 on success; 0 on failure
* Desc: if there is an entry for given id, *priority is assigned 
*       the associated priority and 1 is returned.
*       Otherwise 0 is returned and *priority has no meaning.
* Runtime:  O(1)
*
*/


int pq_get_priority(PQ * pq, int id, double *priority)
{

  if (id < 0 || id >= pq->cap)
  {
    return 0;
  }

  if(pq->arrayId[id].isThere == 0 )
  {
    return 0;
  }

  if(pq->arrayId[id].isThere == 1)
  {
    *priority = pq->arrayPri[pq->arrayId[id].position].priority;
    return 1;
  }
}

/**
* Function: pq_delete_top
* Parameters: priority queue pq
*             int pointers id and priority ("out" parameters)
* Returns: 1 on success; 0 on failure (empty priority queue)
* Desc: if queue is non-empty the "top" element is deleted and
*       its id and priority are stored in *id and *priority; 
*       The "top" element will be either min or max (wrt priority)
*       depending on how the priority queue was configured.
*    
*       If queue is empty, 0 is returned.
*
* Runtime:  O(log n)
*
*22.5  32.5 37.5 
*/

int pq_delete_top(PQ * pq, int *id, double *priority)
{
  int i =1;


  if(pq->size <= 1)
  {
    return 0;
  }
  else{
    *priority = pq->arrayPri[1].priority;
    *id = pq->arrayPri[1].id;
    //printf("\nid: %d, prioriti: %f\n", *id, *priority);
    //printf("\nSize: %d\n", pq->size);
    pq_remove_by_id(pq, *id);
    
    return 1;
  }
}

/**
* Function: pq_peek_top
* Parameters: priority queue pq
*             int pointers id and priority ("out" parameters)
* Returns: 1 on success; 0 on failure (empty priority queue)
* Desc: if queue is non-empty information about the "top" 
*       element (id and priority) is stored in *id and *priority; 
*       The "top" element will be either min or max (wrt priority)
*       depending on how the priority queue was configured.
*
*       The priority queue itself is unchanged (contrast with
*       pq_delete_top).!
*    
*       If queue is empty, 0 is returned.
*
* Runtime:  O(1)
*
*/
int pq_peek_top(PQ * pq, int *id, double *priority)
{
  if(pq->size <= 1)
  {
    return 0;
  }

  *id = pq->arrayPri[1].id;
  *priority = pq->arrayPri[1].priority;

}

/**
* Function:  pq_capacity
* Parameters: priority queue pq
* Returns: capacity of priority queue (as set on creation)
* Desc: see returns
*
* Runtime:   O(1)
*
*/ 
int pq_capacity(PQ * pq)
{
  return pq->cap;
}

/**
* Function: pq_size
* Parameters: priority queue pq
* Returns: number of elements currently in queue
* Desc: see above
*
* Runtime:  O(1)
*/

int pq_size(PQ * pq)
{
  return pq->size-1;
}
