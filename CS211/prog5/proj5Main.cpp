<<<<<<< HEAD
/* This file contains the user interface code for the Infix Evaluation Project
 *  Project 5 for CS 211 for Fall 2017
 *
 * Date: 03/19/2018
 *
 * Author: Lachezar Lyubenov
 *
 */

#include "proj5Tokens.h"
#include "myStack.h"

bool debugMode = false;

void printCommands();

void processExpression (Token inputToken, TokenReader *tr, myStack &numberArray, myStack &operatorArray);

int eval (int firstValue, char operation, int secondValue)
{
        if (operation == '+') return firstValue + secondValue;
        else if (operation == '-') return firstValue - secondValue;
        else if (operation == '*') return firstValue * secondValue;
        else if (operation == '/') return firstValue / secondValue;
        else{
                return -9999;
        }
}

void popAndEval (myStack* operatorArray, myStack* numberArray)
{
        char operation = operatorArray->top();
        operatorArray->pop(operatorArray->top());

        int secondValue = numberArray->top();
        numberArray->pop(operatorArray->top());

        int firstValue = numberArray->top();
        numberArray->pop(operatorArray->top());

        int result = 0;
        result = eval ( firstValue, operation, secondValue );
        numberArray->push(result);
}

int main(int argc, char *argv[])
{
        /***************************************************************/
        /* Add code for checking command line arguments for debug mode */

        for (int x = 0; x < argc; ++x)
        {
                if (argv[x] == "-d")
                {
                        debugMode = true;
                }
        }

        Token inputToken;
        TokenReader tr;

        myStack numberArray;
        myStack operatorArray;

        printf ("Starting Expression Evaluation Program\n\n");
        printf ("Enter Expression: ");


        inputToken = tr.getNextToken ();

        while (inputToken.equalsType(QUIT) == false)
        {
                /* check first Token on Line of input */
                if(inputToken.equalsType(HELP))
                {
                        printCommands();
                        tr.clearToEoln();
                }
                else if(inputToken.equalsType(ERROR))
                {
                        printf ("Invalid Input - For a list of valid commands, type ?\n");
                        tr.clearToEoln();
                }
                else if(inputToken.equalsType(EOLN))
                {
                        printf ("Blank Line - Do Nothing\n");
                        /* blank line - do nothing */
                }
                else
                {
                        processExpression (inputToken, &tr, numberArray, operatorArray);
                }

                printf ("\nEnter Expression: ");
                inputToken = tr.getNextToken ();
        }

        printf ("Quitting Program\n");
        return 1;
}

void printCommands()
{
        printf ("The commands for this program are:\n\n");
        printf ("q - to quit the program\n");
        printf ("? - to list the accepted commands\n");
        printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}

void processExpression (Token inputToken, TokenReader *tr, myStack &numberArray, myStack &operatorArray)
{
        /**********************************************/
        /* Declare both stack head pointers here      */

        numberArray.reset();
        operatorArray.reset();

        /* Loop until the expression reaches its End */
        while (inputToken.equalsType(EOLN) == false)
        {

                /* The expression contain a VALUE */
                if (inputToken.equalsType(VALUE))
                {
                        if (debugMode == true)
                        {
                                printf("Val: %d, ", inputToken.getValue());
                        }

                        // add code to perform this operation here
                        numberArray.push(inputToken.getValue());
                }
                /* The expression contains an OPERATOR */
                else if (inputToken.equalsType(OPERATOR))
                {
                        if (inputToken.equalsOperator('('))
                        {
                                if (debugMode == true)
                                {
                                        printf("Val: %d, ", inputToken.getValue());
                                }
                                // add code to perform this operation here
                                operatorArray.push(inputToken.getOperator());
                        }
                        if ((inputToken.equalsOperator('+')) || (inputToken.equalsOperator('-')))
                        {
                                while (!operatorArray.isEmpty() && ((operatorArray.top() == '+' || operatorArray.top() == '-' || operatorArray.top() == '*' || operatorArray.top() == '/')))
                                {
                                        popAndEval (&operatorArray, &numberArray);
                                }
                                if (debugMode == true)
                                {
                                        printf("Val: %d, ", inputToken.getValue());
                                }
                                operatorArray.push(inputToken.getOperator());
                        }
                        if (inputToken.equalsOperator('*') || inputToken.equalsOperator('/'))
                        {
                                while (!operatorArray.isEmpty() && (operatorArray.top() == '*' || operatorArray.top() == '/'))
                                {
                                        popAndEval (&operatorArray, &numberArray);
                                }
                                operatorArray.push(inputToken.getOperator());
                        }
                        if (inputToken.equalsOperator(')'))
                        {
                                while (!operatorArray.isEmpty() && (operatorArray.top() != '('))
                                {
                                        popAndEval (&operatorArray, &numberArray);
                                }
                                if (operatorArray.isEmpty())
                                {
                                        printf ("Error!");
                                }
                                else{
                                        operatorArray.pop(inputToken.getOperator());
                                }
                        }
                }

                /* get next token from input */
                inputToken = tr->getNextToken ();
        }

        /* The expression has reached its end */
        printf ("\n");

        // add code to perform this operation here
        while (!operatorArray.isEmpty())
        {
                popAndEval (&operatorArray, &numberArray);
        }
        if (debugMode == true)
        {
                printf("Expression is done, result below:");
        }

        printf ("Answer: %d", numberArray.top());

        numberArray.reset();
        operatorArray.reset();

        if (!numberArray.isEmpty())
        {
                printf ("Error! Not empty!");
        }
        printf ("\n");

}
=======
/* This file contains the user interface code for the Infix Evaluation Project
 *  Project 5 for CS 211 for Fall 2017
 *
 * Date: 03/19/2018
 *
 * Author: Lachezar Lyubenov
 *
 */

#include "proj5Tokens.h"
#include "myStack.h"

bool debugMode = false;

void printCommands();

void processExpression (Token inputToken, TokenReader *tr, myStack &numberArray, myStack &operatorArray);

int eval (int firstValue, char operation, int secondValue)
{
        if (operation == '+') return firstValue + secondValue;
        else if (operation == '-') return firstValue - secondValue;
        else if (operation == '*') return firstValue * secondValue;
        else if (operation == '/') return firstValue / secondValue;
        else{
                return -9999;
        }
}

void popAndEval (myStack* operatorArray, myStack* numberArray)
{
        char operation = operatorArray->top();
        operatorArray->pop(operatorArray->top());

        int secondValue = numberArray->top();
        numberArray->pop(operatorArray->top());

        int firstValue = numberArray->top();
        numberArray->pop(operatorArray->top());

        int result = 0;
        result = eval ( firstValue, operation, secondValue );
        numberArray->push(result);
}

int main(int argc, char *argv[])
{
        /***************************************************************/
        /* Add code for checking command line arguments for debug mode */

        for (int x = 0; x < argc; ++x)
        {
                if (argv[x] == "-d")
                {
                        debugMode = true;
                }
        }

        Token inputToken;
        TokenReader tr;

        myStack numberArray;
        myStack operatorArray;

        printf ("Starting Expression Evaluation Program\n\n");
        printf ("Enter Expression: ");


        inputToken = tr.getNextToken ();

        while (inputToken.equalsType(QUIT) == false)
        {
                /* check first Token on Line of input */
                if(inputToken.equalsType(HELP))
                {
                        printCommands();
                        tr.clearToEoln();
                }
                else if(inputToken.equalsType(ERROR))
                {
                        printf ("Invalid Input - For a list of valid commands, type ?\n");
                        tr.clearToEoln();
                }
                else if(inputToken.equalsType(EOLN))
                {
                        printf ("Blank Line - Do Nothing\n");
                        /* blank line - do nothing */
                }
                else
                {
                        processExpression (inputToken, &tr, numberArray, operatorArray);
                }

                printf ("\nEnter Expression: ");
                inputToken = tr.getNextToken ();
        }

        printf ("Quitting Program\n");
        return 1;
}

void printCommands()
{
        printf ("The commands for this program are:\n\n");
        printf ("q - to quit the program\n");
        printf ("? - to list the accepted commands\n");
        printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}

void processExpression (Token inputToken, TokenReader *tr, myStack &numberArray, myStack &operatorArray)
{
        /**********************************************/
        /* Declare both stack head pointers here      */

        numberArray.reset();
        operatorArray.reset();

        /* Loop until the expression reaches its End */
        while (inputToken.equalsType(EOLN) == false)
        {

                /* The expression contain a VALUE */
                if (inputToken.equalsType(VALUE))
                {
                        if (debugMode == true)
                        {
                                printf("Val: %d, ", inputToken.getValue());
                        }

                        // add code to perform this operation here
                        numberArray.push(inputToken.getValue());
                }
                /* The expression contains an OPERATOR */
                else if (inputToken.equalsType(OPERATOR))
                {
                        if (inputToken.equalsOperator('('))
                        {
                                if (debugMode == true)
                                {
                                        printf("Val: %d, ", inputToken.getValue());
                                }
                                // add code to perform this operation here
                                operatorArray.push(inputToken.getOperator());
                        }
                        if ((inputToken.equalsOperator('+')) || (inputToken.equalsOperator('-')))
                        {
                                while (!operatorArray.isEmpty() && ((operatorArray.top() == '+' || operatorArray.top() == '-' || operatorArray.top() == '*' || operatorArray.top() == '/')))
                                {
                                        popAndEval (&operatorArray, &numberArray);
                                }
                                if (debugMode == true)
                                {
                                        printf("Val: %d, ", inputToken.getValue());
                                }
                                operatorArray.push(inputToken.getOperator());
                        }
                        if (inputToken.equalsOperator('*') || inputToken.equalsOperator('/'))
                        {
                                while (!operatorArray.isEmpty() && (operatorArray.top() == '*' || operatorArray.top() == '/'))
                                {
                                        popAndEval (&operatorArray, &numberArray);
                                }
                                operatorArray.push(inputToken.getOperator());
                        }
                        if (inputToken.equalsOperator(')'))
                        {
                                while (!operatorArray.isEmpty() && (operatorArray.top() != '('))
                                {
                                        popAndEval (&operatorArray, &numberArray);
                                }
                                if (operatorArray.isEmpty())
                                {
                                        printf ("Error!");
                                }
                                else{
                                        operatorArray.pop(inputToken.getOperator());
                                }
                        }
                }

                /* get next token from input */
                inputToken = tr->getNextToken ();
        }

        /* The expression has reached its end */
        printf ("\n");

        // add code to perform this operation here
        while (!operatorArray.isEmpty())
        {
                popAndEval (&operatorArray, &numberArray);
        }
        if (debugMode == true)
        {
                printf("Expression is done, result below:");
        }

        printf ("Answer: %d", numberArray.top());

        numberArray.reset();
        operatorArray.reset();

        if (!numberArray.isEmpty())
        {
                printf ("Error! Not empty!");
        }
        printf ("\n");

}
>>>>>>> a6d97162d4cf417e38a009717e669e5b9bd310b4
