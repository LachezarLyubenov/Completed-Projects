#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX_LENGTH 300
#define QUIT "q"

int debugMode = 0;

typedef struct Node{
    char *arrayPointer;
    int arraySize;
    int stackTop;
}Node;

//Function to initialte the stack
void initializeStack(Node *Stack)
{
    Stack->arraySize = 2;
    Stack->stackTop = 0;
    char *openingSymbolArray = (char *) malloc(sizeof(char) * (Stack->arraySize));
    Stack->arrayPointer = openingSymbolArray;
}


//Function to check if the stack is empty
int isStackEmpty(Node *Stack)
{
    if (Stack->stackTop == 0)
    {
        return 1;
    }else{
        return 0;
    }
}

//Function to push opening/closing symbols onto the stack
void pushOnto(Node *Stack, int val)
{
    int counter;
    if(debugMode == TRUE)
    {
        printf("\nDEBUG MODE: PUSH\n");
    }

    if (Stack->stackTop == Stack->arraySize)
    {
        char *tempArray = (char *)malloc((sizeof(char) * (Stack->arraySize))+2);
        for (counter = 0; counter < Stack->arraySize; counter++)
        {
            tempArray[counter] = Stack->arrayPointer[counter];
        }
        if(debugMode == TRUE)
        {
            printf("\nNumber of values copied: %d", counter);
        }
        free (Stack->arrayPointer);
        if(debugMode == TRUE)
        {
            printf("\nOld Size: %d", Stack->arraySize);
        }
        Stack->arrayPointer = tempArray;
        Stack->arraySize += 2;
    }
    Stack->arrayPointer[Stack->stackTop] = val;
    if(debugMode == TRUE)
    {
        printf("\nPushed to stack: %c", Stack->arrayPointer[Stack->stackTop]);
    }
    (Stack->stackTop) += 1;
}

//Function to pop an element off of the stack
void popOff(Node *Stack)
{
    if(debugMode == TRUE)
    {
        printf("\nDEBUG MODE: POP\n");
        printf("\nPopped from stack: %c", Stack->arrayPointer[Stack->stackTop]);
    }
    (Stack->stackTop) -= 1;
    Stack->arrayPointer[Stack->stackTop] = 0;
}

//FUnction to reset stack
void StackReset(Node *Stack)
{
    Stack->arraySize = 2;
    Stack->stackTop = 0;
    char *tempArray = (char *) malloc(sizeof(char) * (Stack->arraySize));
    Stack->arrayPointer = tempArray;
}

//Testing purposes print the stack function
void printStack(Node *Stack)
{
    int counter;
    for (counter = 0; counter < Stack->arraySize; counter++)
    {
        printf("%c ", Stack->arrayPointer[counter]);
    }
}

//Function that access the top element on the stack
char getTop(Node *Stack)
{
    return Stack->arrayPointer[Stack->stackTop - 1];
}

//function that checks for equallity
char pairCheck(char openingSymbol, char closingSymbol)
{
    switch (openingSymbol) {
        case '{': return closingSymbol == '}'; break;
        case '(': return closingSymbol == ')'; break;
        case '<': return closingSymbol == '>'; break;
        case '[': return closingSymbol == ']'; break;
        default: return '\0';
    }
}

//function that returns corresponding needed symbol
char neededSymbol(char value)
{
    if (value == '(') return ')';
    if (value == ')') return '(';
    if (value == '[') return ']';
    if (value == ']') return '[';
    if (value == '<') return '>';
    if (value == '>') return '<';
    if (value == '{') return '}';
    if (value == '}') return '{';
}

//Main Function for the program
int main(int argc, char** argv)
{
    char userInput[MAX_LENGTH];
    int counter, j;
    char openingSymbol, closingSymbol;
    Node Stack;

    initializeStack(&Stack);

    //sets debug mode
    for(counter = 0; counter < argc; counter++){
        if(strcmp(argv[counter], "-d") == 0){
            printf("\nDEBUG MODE ON\n");
            debugMode = TRUE;
        }
    }

    //main while loop for checking for balance
    while(TRUE)
    {
        int balanced = 1;
        printf("\n\nYou can now enter expression to be checked for balance or type 'q' to exit: \n");
        fgets(userInput, MAX_LENGTH, stdin);

        if(userInput[0] == 'q' || userInput[0] == 'Q')
        {
            printf("\n\nExiting the program...\n\n");
            exit(0);
        }

        for(counter = 0; counter < strlen(userInput) -1; counter++)
        {
            if(userInput[counter] == '(' || userInput[counter] == '{' || userInput[counter] == '[' || userInput[counter] == '<')
            {
                pushOnto(&Stack, userInput[counter]);
            }
            if(userInput[counter] == ')' || userInput[counter] == '}' || userInput[counter] == ']' || userInput[counter] == '>')
            {
                if(isStackEmpty(&Stack) ==1 || pairCheck(Stack.arrayPointer[Stack.stackTop-1],userInput[counter])== 0)
                {
                    balanced = 0;
                    break;
                }
                else if(isStackEmpty(&Stack) ==0 || pairCheck(userInput[counter], Stack.arrayPointer[Stack.stackTop-1]== 1))
                {
                    popOff(&Stack);
                    balanced = 1;
                    continue;
                }
                else
                {
                    pushOnto(&Stack, userInput[counter]);
                }
            }
        }
        if(isStackEmpty(&Stack)==1 && balanced == 1){
            printf("Expression is balanced!\n");
        }
        else if (isStackEmpty(&Stack) == 1 && balanced == 0 ) {
            for(j = 0; j < counter; j++){
                printf(" ");
            }
            printf("^ missing %c\n\n", neededSymbol(userInput[counter]));
        }
        else if (isStackEmpty(&Stack) == 0 && balanced == 0) {
            for(j = 0; j < counter; j++){
                printf(" ");
            }
            printf("^ expecting %c\n\n", neededSymbol(Stack.arrayPointer[Stack.stackTop-1]));
        }
        else if (isStackEmpty(&Stack) == 0 && balanced == 1) {
            for(j = 0; j < counter; j++){
                printf(" ");
            }
            printf("^ missing %c\n\n", neededSymbol(Stack.arrayPointer[Stack.stackTop-1]));
        }
        StackReset(&Stack);
    }
}
