#include <stdio.h>
#include <stdlib.h>

void printArray(int arr[], int n)
{
   int i;
   for (i=0; i < n; i++)
      {
       printf(" \t %d ", arr[i]);
      }
   printf("\n");
}

void arrayCopy(int fromArray[], int toArray[], int count)
{
  int i;

  for(i = 0; i < count; i++)
  {
    toArray[i] = fromArray[i];
  }
}

void myFavoriteSort(int firstArray[], int sortSize)
{
   int i, insertKey, j;
   for (i = 0; i < sortSize; i++)
   {
       insertKey = firstArray[i];
       j = i-1;

       /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
       while (j >= 0 && firstArray[j] > insertKey)
       {
           firstArray[j+1] = firstArray[j];
           j = j-1;
       }
       firstArray[j+1] = insertKey;
   }
}

int linSearch (int arr[], int size, int target, int* numComparisons)
{
  *numComparisons = 0;
  int searchValue = target;
  int i;
  for (i = 0 ; i < size; i++)
  {
      if (arr[i] == searchValue)     /* if required element found */
      {
         break;
      }
   (*numComparisons)++;
  }
  if (i == size)
  {
     return -1;
  }
  else
  {
     return i;
  }
}
/*
//int binSearch (int arr[], int size, int target, int* numComparisons)
int binSearch(int arr[], int target, int low, int high, int* numComparisons)
{
  int beginArray = arr[0];
  int endArray = arr[size-1];
  int search = target;

  int search = target;
  int beginArray = low;
  int endArray = high;

  int mid = (beginArray + endArray)/2;

  while (beginArray <= endArray)
  {
    (*numComparisons)++;
    int mid = (beginArray + endArray)/2;
    if (arr[mid] == search)
    {
      return mid;
    }
    if (arr[mid] < search)
    {
      return binSearch(arr, target, beginArray, mid-1, numComparisons);
    }
    else if (arr[mid] < search)
    {
      return binSearch(arr, target, mid+1, endArray, numComparisons);
    }
    else
      return -1;
  }
}
*/
int binSearch(int arr[], int target, int low, int high, int* numComparisons)
//int recBinarySearch(int arr[], int key, int low, int high)
{
  (*numComparisons)++;
  if (high >= low)
  {
       int mid = low + (high - low)/2;

       // If the element is present at the middle
       // itself
       if (arr[mid] == target)
           return mid;

       // If element is smaller than mid, then
       // it can only be present in left subarray
       if (arr[mid] > target)
           return binSearch(arr, target, low, mid-1, numComparisons);

       // Else the element can only be present
       // in right subarray
       else
       return binSearch(arr, target, mid+1, high, numComparisons);
  }
  return -1;

}

/*  int mid = (beginArray + endArray)/2;
  while (beginArray < endArray)
  {
    (*numComparisons)++;
    if (arr[mid] == search)
    {
      return mid;
    }

    if (arr[mid] < search)
    {
      return binSearch(arr, size+1, target, numComparisons);
    }
    else if (arr[mid] > search)
    {
      return binSearch(arr, size-1, target, numComparisons);
    }
  }
  return -1; */



int main(int argc, char **argv)
{
  int search;
  int count,i, val = 0;

  int *firstArray;
  int *secondArray;
  int size = 100;
  int linearNumCompare, binaryNumCompare;
  int binSearchPosition,linSearchPosition;

  firstArray = (int *) malloc (size * sizeof(int) );
  secondArray = (int *) malloc (size * sizeof(int) );

  //Reading Values into Array
  printf("\n Enter an Integer (-999 to stop): ");
  scanf("%d",&val);

  while(val!=-999)
  {
  firstArray[i] = val;
  i++;
  printf("\n Enter an Integer (-999 to stop): ");
  scanf("%d",&val);

  count = i;

  if (count >= size)
  {
    firstArray = (int *) malloc (size * sizeof(int) );
    secondArray =  (int *) malloc (size * sizeof(int) );
    int *temp, *temp2;
    temp = (int *) malloc ( size * 2 * sizeof(int) );
    temp2 = (int *) malloc ( size * 2 * sizeof(int) );

    for ( i = 0 ; i < size ; i++)
    {
        temp[i] = firstArray[i];
        temp2[i] = secondArray[i];
    }
    free (temp);
    free (temp2);
    firstArray = temp;
    secondArray = temp2;
    size = size * 2;
  }
  }

  printf("\n Array One: \n");
  printArray(firstArray, count);

  printf("\n Array Two: \n");
  arrayCopy(firstArray, secondArray, count);
  printArray(secondArray, count);

  printf("\n Sorted Array (Array One): \n");
  myFavoriteSort(firstArray, count);
  printArray(firstArray, count);

  printf("\n Enter a number to search: ");
  scanf("%d", &search);
  printf("\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");

  do{
  printf("\n Searching within the Unsorted Array Number Two using Linear Search: \n\n");
  linSearchPosition = linSearch (secondArray, size, search, &linearNumCompare);
    if(linSearchPosition == -1)
    {
      printf("\n Search value is not present within the array!\n");
    }
    else
    {
      printf(" Search Value is located at position: %d",linSearchPosition+1);
      printf("\n Linear search comparisons: %d \n", linearNumCompare+1);
    }

    printf("\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n\n");
    printf(" Searching within the Sorted Array Number One using Binary Search:\n");
    int low = firstArray[0];
    int high = sizeof(firstArray)-1;
    printArray(firstArray, count);
    //binSearchPosition = binSearch (firstArray, count, search, &binaryNumCompare);
    binSearchPosition = binSearch (firstArray, search, low, high, &binaryNumCompare);

      if(binSearchPosition == -1)
      {
        printf("\n\n Search value is not present within the array!\n");
      }
      else
      {
        printf("\n Search Value is located at position: %d",binSearchPosition+1);
        printf("\n Binary search comparisons: %d \n\n", binaryNumCompare-1);
      }
    }while(val != -999);

return 0;
}
