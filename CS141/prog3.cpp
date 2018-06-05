/* --------------------------------------------------------
 * Program: #3, 0/1 Guessing Game 

 * Welcome to the 0/1 guessing game!                                  
                                                                   
 * Enter 0 or 1, trying to outsmart the computer, which is going to   
 * attempt to forecast your guesses.  On each move the score indicator
 * moves to the right if the computer guesses correctly, and moves    
 * to the left if the computer does not.                              
    Enter 't' to toggle displaying the data table.                 
    Enter 'r' to reset the board.                                  
    Enter 'x' to exit.                                             
 * Good luck, you'll need it!  

 * Class: Program #3 for CS 141, Fall 2017.  
 * Lab: 12PM Tuesday,
 * TA ???
 * System: Mac OS X && Windows 10
 * Author: Lachezar Lyubenov
*/


#include <iostream>
#include <iomanip>
#include <string>
#define ROW 2
#define COLUMN 8
using namespace std;


//*****ALL FUNCTION DECLARATIONS*****
void displayIDInfo  ();        		
void displayInstr   ();
void displayTable   (int twoDarray[ROW][COLUMN], char oneDarray[], bool &toggle, int guess);
void changeTable    (int table[ROW][COLUMN], char input, int place);
void forecastNumber (int array[ROW][COLUMN], int place, int &prediction, char previous);
void resetTable     (int array[ROW][COLUMN], char arrayTwo[3], int &newScore, int &turns);
void tableClear     (int array[ROW][COLUMN]);
void displayBoard   (int number, bool checker);
void gameOver	    ();
void scorePoint	    (int &points,char human, int computer);
int  convertFunction(int first, int second, int third); 
void firstMoves	    (int &turn, char &moveVar, int &points);
void myMoves        (int &turnPhase, char &changeVar, bool &checker, bool &tab);
void shuffleNumbers (char theNumbers[]);


// Display Program Information
//----------------------------------------------------------------------------------------------------------
void displayIDInfo()
{
    cout << "Author: Lachezar Lyubenov" 		<< endl;
    cout << "Author: Narayan Israel Guerrero"	<< endl;    
	cout << "Lab: Tuesday, 12pm"				<< endl;
	cout << "Program: #3, 0/1 Guessing Game"	<< endl;
	cout << "-----------------------------------------------------------------"	<< endl;
	cout << endl;
}//end displayIDInfo()


// Display Instructions
//----------------------------------------------------------------------------------------------------------
void displayInstr()
{
    cout << "Program: #3, 0/1 Guessing Game                                     " << endl
         << "Welcome to the 0/1 Guessing game!                                  " << endl                                 
         << "                                                                   " << endl    
         << "Enter 0 or 1, trying to outsmart the computer, which is going to   " << endl   
         << "attempt to forecast your guesses.  On each move the score indicator" << endl
         << "moves to the right if the computer guesses correctly, and moves    " << endl
         << "to the left if the computer does not.                              " << endl                        
         << "    Enter 't' to toggle displaying the data table.                 " << endl              
         << "    Enter 'r' to reset the board.                                  " << endl                                  
         << "    Enter 'x' to exit.                                             " << endl                                            
         << " Good luck, you'll need it!                                        " << endl << endl << endl;
}//end displayInstr()


//Function that erases all values of 2D array
//----------------------------------------------------------------------------------------------------------
void tableClear (int array[ROW][COLUMN])
{
	for (int i = 0; i < ROW; i++) 
	{
		for (int j = 0; j < COLUMN; j++) {array[i][j] = 0;}
	}
}//end tableClear()


//This function takes last three inputs, then returns a column for the table to use
//----------------------------------------------------------------------------------------------------------
int convertFunction (int first, int second, int third) 
{	
	first  = (first  -'0');
	second = (second -'0');
	third  = (third  -'0');
	int total = 0;
		
	if (first ) {total += 4;}
	if (second) {total += 2;}
	if (third ) {total += 1;}
	return total;	
}//end convertFunction()


//Function for Moves /Input/
//----------------------------------------------------------------------------------------------------------
void myMoves (int &turnPhase, char &changeVar, bool &checker, bool &tab)
{
    cout << endl << turnPhase << ". Your input: "; 	
	cin >> changeVar;
	changeVar = toupper(changeVar);
	
	if ((changeVar == '0') || (changeVar == '1')) 
	{
		turnPhase++;
		cout << endl;
	}
	else if (changeVar == 'X') { gameOver();}
	else if (changeVar == 'R') { checker = true;}
	else if (changeVar == 'T') {(tab =!tab);}
	else    {cout << "Invalid Input !" << endl; myMoves(turnPhase, changeVar, checker, tab);}
	return;
}//end myMoves()


//Function displays score with most recent data and check for WIN.
//----------------------------------------------------------------------------------------------------------
void displayBoard(int number, bool checker)
{
	if (!checker)
	{
	    cout << "Computer        Human" << endl;
	    char board[] = { 'x','-','-','-','-','-','-','-','-','-','x','+','+','+','+','+','+','+','+','+','x'};
	    for (int i = 0; i <= 21; i++) 
	    {
	            cout << board[i];
	    }
	    cout << endl;
	    for (int i = 0; i<=21; i++) 
	    {
	        if ( i == number) 
	        {
	            cout << setw(number+1) << '^' << endl;
	        }
	    }
	    if (number == 0) {
			cout << "Computer wins, WE ARE DOOMED!" << endl << endl;
		    cout << "Thank you for playing.  Exiting..." << endl;
			exit(0);
		}
		else if (number == 20) {
			cout << "There is Hope for Humanity, Human wins!" << endl << endl;
		    cout << "Thank you for playing.  Exiting..." << endl;
			exit(0);
		}
	}
}//end displayBoard()


//Function displays table with most recent data
//----------------------------------------------------------------------------------------------------------
void displayTable(int twoDarray[ROW][COLUMN], char oneDarray[], bool &toggle, int guess) 
{
	if (toggle) {
	cout << "       0    1" 									<< endl;
	cout << "      ---  ---"									<< endl;
	cout << "000    " << twoDarray[0][0] << "    " << twoDarray[1][0]	<< endl;
	cout << "001    " << twoDarray[0][1] << "    " << twoDarray[1][1]	<< endl;
	cout << "010    " << twoDarray[0][2] << "    " << twoDarray[1][2]	<< endl;
	cout << "011    " << twoDarray[0][3] << "    " << twoDarray[1][3]	<< endl;
	cout << "100    " << twoDarray[0][4] << "    " << twoDarray[1][4]	<< endl;
	cout << "101    " << twoDarray[0][5] << "    " << twoDarray[1][5]	<< endl;
	cout << "110    " << twoDarray[0][6] << "    " << twoDarray[1][6]	<< endl;
	cout << "111    " << twoDarray[0][7] << "    " << twoDarray[1][7]	<< endl;
	cout << "Previous three: " << oneDarray[0] << oneDarray[1] << oneDarray[2] << ".   " << "Forecast:" << guess << endl;
	}
}//end displayTable()


//Function that shuffles the three numbers
//----------------------------------------------------------------------------------------------------------
void shuffleNumbers (char theNumbers[3])
{
	char swapOne   = theNumbers[1];
	char swapTwo   = theNumbers[2];
	char swapThree = theNumbers[0];	
	theNumbers[0]  = swapOne;
	theNumbers[1]  = swapTwo;
	theNumbers[2]  = swapThree;
}//end shuffleNumbers()


//Changes 2D array after every input from the player
//----------------------------------------------------------------------------------------------------------
void changeTable(int table[ROW][COLUMN], char input, int place)
{
	int row = (input - '0');
	table[row][place]++;
}//end changeTable()


//Function allows the user to manually enter table values and start game over
//----------------------------------------------------------------------------------------------------------
void resetTable(int array[ROW][COLUMN], char arrayTwo[3], int &newScore, int &turns)
{
	arrayTwo[0] = '0';
	arrayTwo[1] = '0';
	arrayTwo[2] = '0';
	turns = 1;
	newScore = 10;
	cout << endl;
	
	cout << "Enter 16 single-digit numbers separated by spaces to set the moves table." << endl;
	
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++) { cin >> array[i][j];}
	}
	cout << endl;
}//end resetTable()


//Computer Prediction of next number based on previous groups
//----------------------------------------------------------------------------------------------------------
void forecastNumber(int array[ROW][COLUMN], int place, int &prediction, char previous)
{
	if      (array[0][place] > array[1][place])  { prediction = 0;}
	else if (array[0][place] < array[1][place])  { prediction = 1;}
	else if (array[0][place] == array[1][place]) { previous == '0' ? (prediction = 1) : (prediction = 0);}
}//end forecastNumber()


//Function compares Computer prediction to Human choices for scoring of points
//----------------------------------------------------------------------------------------------------------
void scorePoint(int &points,char human, int computer )
{
	int numConv;
	numConv = (human - '0');
	if (computer == numConv)																			//Score board moves left
	{
		points--;
		cout << "Computer gets a point" << endl<< endl;
		if (points == 5) { cout << ">>> You're going to lose! <<<" << endl << endl;}
	}
	else if (computer != numConv)																		//Score Board moves right
	{
		points++;
		cout << "Human gets a point" << endl<< endl;
		if (points == 15) { cout << ">>> You're going to win! <<<" << endl << endl;}
	}
}//end scorePoint()


//Function for gameover.
//----------------------------------------------------------------------------------------------------------
void gameOver()
{    
	cout << endl;
    cout << "Thank you for playing.  Exiting..." << endl;
    exit(0);
}//end gameOver()


//Main Function of program
//-----------------------------------------------------------
int main() {
	
    displayIDInfo();   					//Display ID info
    displayInstr ();  					//Display game instructions

    char myThree[3] = {'0','0','0'}, previousThree[3], myLast;
	
    int myTable[ROW][COLUMN], turnCounter = 1, score = 10, 
		forecast = 1, newPlace = 0, previousPlace;		
																	
    bool start = true, reset = false, showTable = false, skipShuffle = false;
		     
    tableClear(myTable);																	
	displayBoard(score, reset);
	
	//Main Loop of Program											
	while (reset == false)											
	{	
 		if (start) 
		{
			for (int num = 0; num <=2; num++)																	//Loop runs for first three inputs - 'R' & 'T' re-adjust loop
			{
				myLast = myThree[num];

			 	myMoves(turnCounter, myThree[num], reset, showTable );											
				
				if (reset) { resetTable(myTable,myThree, score,turnCounter); num = -1; reset= false; continue;} //Checks for Toggle display table
				else if (myThree[num] == 'T') 
				{
					displayBoard(score, reset);
					myThree[num]=myLast; 
					num = -1;
				} 
				else 
				{
					scorePoint(score, myThree[num],forecast);													//Updates the score board
					(myThree[num] == '0') ? (forecast = 1) : (forecast = 0);
					
					displayBoard(score, reset);
				}
				displayTable(myTable, myThree, showTable, forecast);											//Displays table is toggle is on
			}
			start = false;
		}
		previousPlace = convertFunction(myThree[0], myThree[1], myThree[2]);									//Store last three before any shuffle or changes
		previousThree[0] = myThree[0];
		previousThree[1] = myThree[1]; 
		previousThree[2] = myThree[2];
		
		shuffleNumbers(myThree);
		myLast = myThree[2];
		myMoves(turnCounter, myThree[2], reset, showTable);														//Cycles here for input after shuffle and before update 2D array
		
		if (reset) { resetTable(myTable,myThree, score,turnCounter); start=true; reset=false; continue;}
		else if (myThree[2] == 'T') 
		{
			displayBoard(score, reset);
			myThree[2]= myLast; 
			shuffleNumbers(myThree);																			//Need to shuffle twice to return to previous position after loop iteration
			shuffleNumbers(myThree);
		} 
		else 
		{
			scorePoint(score, myThree[2],forecast);
			displayBoard(score, reset);
			newPlace = convertFunction(myThree[0], myThree[1], myThree[2]);
			changeTable(myTable, myThree[2], previousPlace);
			forecastNumber (myTable, newPlace, forecast, myThree[2]);											//Where the computer analyzes the inputs and predicts
		}
		displayTable(myTable, myThree, showTable, forecast);
	}
	gameOver();
return 0;
}//end main()
