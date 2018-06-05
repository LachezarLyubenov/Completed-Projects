/*
 Programming Project 1
 CS 211
 Lachezar Lyubenov - llyube2
 Program that deals with dynamically allocated arrays in C, different search algorithms
 and sorting algorithms. Code is written in C
*/
#include <stdio.h>
#include <stdlib.h>

//Array copy function
//----------------------------------------------------------
void arrayCopy(int* fromArray, int* toArray, int count)
{
  int i;

  for(i = 0; i < count; i++)
  {
    toArray[i] = fromArray[i];
  }
}//end arrayCopy()

//Insertion sort function
//----------------------------------------------------------
void myFavoriteSort(int* firstArray, int sortSize)
{
   int i, insertKey, j;
   for (i = 0; i < sortSize; i++)
   {
       insertKey = firstArray[i];
       j = i-1;

       while (j >= 0 && firstArray[j] > insertKey)
       {
           firstArray[j+1] = firstArray[j];
           j = j-1;
       }
       firstArray[j+1] = insertKey;
   }
}//end myFavoriteSort()

//Linear search function
//----------------------------------------------------------
int linSearch (int* arr, int size, int target, int* linearNumCompare)
{
  *linearNumCompare = 0;
  int searchValue = target;
  int i;
    
  for (i = 0 ; i < size; i++)
  {
      (*linearNumCompare)++;
      
      //if target value found - return position
      if (arr[i] == searchValue)
      {
         return i;
      }
  }
  return -1;
}//end linSearch()

//Binary search function
//----------------------------------------------------------
int binSearch(int arr[], int target, int low, int high, int* binaryNumCompare)
{
  (*binaryNumCompare)++;
  
  if (high >= low)
  {
       int mid = (high + low)/2;

       // If target number is found, return mid
       if (arr[mid] == target)
       {
           return mid;
       }
      
       // If target is smaller than mid, search left side
       if (arr[mid] > target)
       {
           return binSearch(arr, target, low, mid-1, binaryNumCompare);
       }
       // Else the target number is on right side
      else{
      return binSearch(arr, target, mid+1, high, binaryNumCompare);
      }
  }
  return -1;
}//end binSearch()

//Print array function - helper function for testing purposes
//----------------------------------------------------------
void printArray(int* arr, int n)
{
    int i;
    for (i=0; i < n; i++)
    {
        printf(" \t %d ", arr[i]);
    }
    printf("\n");
}//end printArray()

//Main function for the program
//----------------------------------------------------------
int main()
{
  int search;
  int val = 0;
  int i;

  int *firstArray;
  int *secondArray;
  int size = 0;
  int linearNumCompare = 0;
  int binaryNumCompare = 0;

  firstArray = (int *) malloc (sizeof(int) );
    
  //Reading Values into Array One
  printf("\n Enter an Integer (-999 to stop): ");
  scanf("%d",&val);

  //Loop that populates the first array
  while(val!=-999)
  {
      firstArray[size] = val;
      size++;
      firstArray = (int *) realloc (firstArray, (size+1) * sizeof(int) );
      scanf("%d",&val);
  }
    
 // secondArray = (int *) malloc (size * sizeof(int) );
  arrayCopy(firstArray, secondArray, size);
  myFavoriteSort(firstArray, size);

//Helper code for printing/troubleshooting the arrays.
/*----------------------------------------------------------
  //printf("\n Array One: \n");
  //printArray(firstArray, size);

  //printf("\n Array Two: \n");
  //printArray(secondArray, size);

  //printf("\n Sorted Array (Array One): \n");
  //printArray(firstArray, size);
*/
  
  //Print Statement to request Search Parameter
  printf("\n Enter a number to search: ");
  printf("\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
  
  //Loop that uses the search parameter to perform the Linear/Binary search
  while(scanf("%d", &search) == 1, search !=-999)
  {
      //Searching in the second array using linear search
      printf("\n Searching within the Unsorted Array Number Two using Linear Search: \n\n");
      int linSearchPosition = linSearch (secondArray, size, search, &linearNumCompare);
      
      if(linSearchPosition == -1)
      {
          printf("\n    Search value of %d is not present within the array!\n", search);
      }
      else
      {
          printf("    Search Value of %d is located at position: %d",search, linSearchPosition+1);
          printf("\n    Linear search comparisons count: %d \n", linearNumCompare);
      }
      
      //Searching in the first array using binary search
      printf("\n Searching within the Sorted Array Number One using Binary Search:\n");
      
      int low = 0;
      int high = size-1;
      binaryNumCompare = 0;
      
      int binSearchPosition = binSearch (firstArray, search, low, high, &binaryNumCompare);

      if(binSearchPosition == -1)
      {
          printf("\n\n  Search value of %d is not present within the array!\n", search);
      }
      else
      {
          printf("\n    Search Value of %d is located at position: %d",search ,binSearchPosition+1);
          printf("\n    Binary search comparisons count: %d \n\n", binaryNumCompare);
      }
      printf("\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n\n");
  }
  return 0;
}
