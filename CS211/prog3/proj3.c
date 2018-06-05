//Lachezar Lyubenov - llyube2
//Maze - Program 3 - CS 211
//Thursday, March 1st.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE   1
#define FALSE  0

int debugMode = 0;

//Structures
typedef struct mazeStruct
{
 char **mazeArray;        //stores 2D maze
 int xSize, ySize;
 int startX, startY;
 int endX, endY;
 int blockedX, blockedY;
 int **wasVisited;        //stores visited positions

} maze;

typedef struct PathNode
{
    int topCoordX, topCoordY;   //stores path coordinates
    struct PathNode * next;
    struct PathNode * prev;
} Stack;

//read maze info from file
void loadMazeFile(FILE *source, int *xSize, int *ySize, int *startX, int *startY, int *endX, int *endY)
{
	while(fscanf (source, "%d %d", &*xSize, &*ySize) != EOF)
  {
		if(*xSize > 0 && *ySize > 0)
    {
      break;
    }
		else{
			printf("Invalid Maze size must be greater than 0. Current are: %d, %d\n", *xSize, *ySize);
			*xSize = -1;
			*ySize = -1;
		}
	}
	while(fscanf (source, "%d %d", &*startX, &*startY) != EOF)
  {
		if(*startX <= *xSize && *startY <= *ySize)
    {
			break;
    }
		else{
			printf("Invalid Maze Start Positions: %d, %d\n", *startX, *startY);
			*startX = -1;
			*startY = -1;
		}
	}
	while(fscanf (source, "%d %d", &*endX, &*endY) != EOF)
  {
		if(*endX <= *xSize && *endY <= *ySize)
    {
			break;
    }
		else{
			printf("Invalid Maze End Positions: %d, %d\n", *endX, *endY);
			*endX = -1;
			*endY = -1;
		}
	}
}//end loadMazeFile()

//function to check if file input is correct
void isValid(int xSize, int ySize, int startX, int startY, int endX, int endY)
{
	//check xsize and ysize
	if((xSize == -1 || ySize == -1) || (startX == -1 || startY == -1) || (endX == -1 || endY == -1))
  {
		printf("\nReached end of file without finding valid size for the maze, start or end\n");
		exit(1);
	}
}//end isValid()

//function to initiate the maze based on the loaded file
void initializeMaze(maze *mazeStruct, int xSize, int ySize, int startX, int startY, int endX, int endY, int *blockedX, int *blockedY, FILE *source)
{
	int i, j;
	//initialize maze size, start, and end positions
	mazeStruct->xSize = xSize;
	mazeStruct->ySize = ySize;
	mazeStruct->startX = startX;
	mazeStruct->startY = startY;
	mazeStruct->endX = endX;
	mazeStruct->endY = endY;

	//allocate arrays using malloc based on xsize and ysize
	mazeStruct->mazeArray = (char **) malloc(sizeof(char *) * (xSize + 2));
	mazeStruct->wasVisited = (int **) malloc(sizeof(int *) * (xSize + 2));
	for(i = 0; i < xSize + 2; i++)
  {
		mazeStruct->mazeArray[i] = (char *) malloc(sizeof(char) * (ySize + 2));
		mazeStruct->wasVisited[i] = (int *) malloc(sizeof(int) * (ySize + 2));
	}
	//creates the maze and marks all of it as not visited
	for (i = 0; i < mazeStruct->xSize + 2; i++)
  {
		for (j = 0; j < mazeStruct->ySize + 2; j++)
    {
			mazeStruct->mazeArray[i][j] = '.';
			mazeStruct->wasVisited[i][j] = 0;
		}
	}
  //for loop that creates borders and marks them as visited for xSize
	for (i=  0; i < mazeStruct->xSize + 2; i++)
  {
		mazeStruct->mazeArray[i][0] = '*';
		mazeStruct->mazeArray[i][mazeStruct->ySize + 1] = '*';
		mazeStruct->wasVisited[i][0] = 1;
		mazeStruct->wasVisited[i][mazeStruct->ySize + 1] = 1;
	}
  //for loop that creates borders and marks them as visited for ySize
	for (i = 0; i < mazeStruct->ySize + 2; i++)
  {
		mazeStruct->mazeArray[0][i] = '*';
		mazeStruct->mazeArray[mazeStruct->xSize + 1][i] = '*';
		mazeStruct->wasVisited[0][i] = 1;
		mazeStruct->wasVisited[mazeStruct->xSize + 1][i] = 1;
	}
  //marks start and end position within the maze
	mazeStruct->mazeArray[mazeStruct->startX][mazeStruct->startY] = 'S';
	mazeStruct->mazeArray[mazeStruct->endX][mazeStruct->endY] = 'E';
	mazeStruct->wasVisited[mazeStruct->startX][mazeStruct->startY] = 1;

  //while loop that checks  and marks the blocked positions within the maze
  while (fscanf (source, "%d %d", &(*blockedX), &(*blockedY)) != EOF)
  {
    mazeStruct->blockedX = *blockedX;
    mazeStruct->blockedY = *blockedY;
    if((*blockedX == startX && *blockedY == startY) || (*blockedX == endX && *blockedY == endY)){
      printf("Invalid Blocking Start Position: %d, %d\n", *blockedX, *blockedY);
      continue;
    }
    mazeStruct->mazeArray[mazeStruct->blockedX][mazeStruct->blockedY] = '*';
    mazeStruct->wasVisited[mazeStruct->blockedX][mazeStruct->blockedY] = 1;
  }
  //fclose(source);
}//end initializeMaze()

//function to print the maze size, starting and ending positions
void printInfo(int xSize, int ySize, int startX, int startY, int endX, int endY){
	printf ("\nThe size of maze is: %d, %d\n", xSize, ySize);
	printf ("Starting point for the maze is: %d, %d\n", startX, startY);
	printf ("Ending point of the maze is: %d, %d\n", endX, endY);
}//end printInfo()

//print visual representation of the maze using the 2D array
void printMaze(maze *mazeStruct)
{
	int i, j;

	for (i = 0; i < mazeStruct->xSize+2; i++)
  {
		for (j = 0; j < mazeStruct->ySize+2; j++)
    {
			printf ("%c", mazeStruct->mazeArray[i][j]);
    }
		printf("\n");
	}
}//end printMaze()

//push element to the path linked list
void pushOnStack(Stack **PathNode, int coordX, int coordY)
{
	Stack *temp = (Stack *) malloc(sizeof(Stack));
	temp->topCoordX = coordX;
	temp->topCoordY = coordY;
	temp->next = *PathNode;
	*PathNode = temp;
}//end pushOnStack()

//check if path linked list is empty
int isStackEmpty(Stack *PathNode){
	if(PathNode == NULL)
  {
		return 1;
  }
	return 0;
}//end isStackEmpty()

//pop element of the linked list
void popOffStack(Stack **PathNode, int debugMode)
{
  Stack *temp = *PathNode;
  if(debugMode == TRUE)
  {
    printf("Pop: (%d, %d)\n", temp->topCoordX, temp->topCoordY);
  }
	if(*PathNode != NULL)
  {
		*PathNode = (*PathNode)->next;
    //free(temp);
		return;
	}
	printf("\nCannot pop an element from an empty list\n");
	return;
}//end popOffStack()

//Depth search alorithm that traverses the maze
void deepSearch(Stack **PathNode, maze *mazeStruct)
{
  int currentPositionX = (*PathNode)->topCoordX;
  int currentPositionY = (*PathNode)->topCoordY;

  do{
    //check if top of the stack is the end position
    if(currentPositionX == mazeStruct->endX && currentPositionY == mazeStruct->endY)
    {
      break;
    }
    //check if top of the stack has unvisited and unblocked neighbor
    if(mazeStruct->wasVisited[currentPositionX][currentPositionY + 1] == 0)
    {
      //push coordinates of unvisited neighbor on the stack
      pushOnStack(PathNode, currentPositionX, currentPositionY++);
      mazeStruct->wasVisited[currentPositionX][currentPositionY] = 1;
    }
    else if(mazeStruct->wasVisited[currentPositionX + 1][currentPositionY] == 0)
    {
      pushOnStack(PathNode, currentPositionX++, currentPositionY);
      mazeStruct->wasVisited[currentPositionX][currentPositionY] = 1;
    }
    else if(mazeStruct->wasVisited[currentPositionX][currentPositionY - 1] == 0)
    {
      pushOnStack(PathNode, currentPositionX, currentPositionY--);
      mazeStruct->wasVisited[currentPositionX][currentPositionY] = 1;
    }
    else if(mazeStruct->wasVisited[currentPositionX - 1][currentPositionY] == 0){ //check up
      pushOnStack(PathNode, currentPositionX--, currentPositionY);
      mazeStruct->wasVisited[currentPositionX][currentPositionY] = 1;
    }
    else
    {
      popOffStack(PathNode, debugMode);
      if(isStackEmpty(*PathNode))
      {
        continue;
      }
      currentPositionX = (*PathNode)->topCoordX;
      currentPositionY = (*PathNode)->topCoordY;
    }
  }while(isStackEmpty(*PathNode) != 1);
}//end deepSearch()

//printing recursively the linked list that stores the path
void printReverse(Stack *PathNode)
{
    Stack *temp = PathNode;
    if (temp->next == NULL)
    {
       return;
    }
    printReverse(temp->next);
    printf("[%d][%d]\t", temp->topCoordX, temp->topCoordY);
    free(temp);
}//end printReverse()

//function to free memmory
void freeMemory(maze *mazeStruct)
{
  realloc(mazeStruct->mazeArray, 0);
  realloc(mazeStruct->wasVisited, 0);
}//end freeMemory()

//main function for maze.c
int main (int argc, char **argv)
{
  maze mazeStruct;
  Stack *PathNode = NULL;
  FILE *source;

  int xSize = -1; int ySize = -1;
  int startX = -1; int startY = -1;
  int endX = -1; int endY = -1;
  int coordX, coordY;
  int blockedX, blockedY;
  char **inputString;
  int i;

  //sets debug mode
  for(i = 0; i < argc; i++)
  {
    if(strcmp(argv[i], "-d") == 0)
    {
      printf("\nDebug mode ON\n");
      debugMode = 1;
    }
    else{
    inputString = &argv[i];
    }
  }
  argv[1] = *inputString;

  if (( source = fopen( argv[1], "r" )) == NULL )
  {
    printf ( "Can't open input file: %s", argv[1] );
    exit(-1);
  }

  loadMazeFile(source, &xSize, &ySize, &startX, &startY, &endX, &endY);
	//check to see if values are valid
	isValid(xSize, ySize, startX, startY, endX, endY);
  //initialize 2D array and maze
  initializeMaze(&mazeStruct, xSize, ySize, startX, startY, endX, endY, &blockedX, &blockedY, source);
	//maze info generated from the source file
	printInfo(xSize, ySize, startX, startY, endX, endY);
  //displays actual maze based on data from 2D array
  printf("\n\tMaze:\n");
  printMaze( &mazeStruct);
  //pushing starting position to the list
  pushOnStack(&PathNode, startX, startY);
  //performing depth search on the maze and storing viable path in the linked list
  deepSearch(&PathNode, &mazeStruct);

  if (PathNode == NULL)
  {
    printf("\nThere is no solution\n");
  }
  else{
    printf("\nThere is solution and its printed below: \n\n");
    printReverse(*&PathNode);
    printf ( "\n");
  }
  printf ( "\n");
  freeMemory(&mazeStruct);

  return 0;
}//end main()
