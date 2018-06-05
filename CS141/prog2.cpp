/* --------------------------------------------------------
 * Traffic.cpp
 *     Text-based version of the game RushHour, where the
 *     object is to move the vehicles such that the small
 *     car can exit the right of the board.
 *
 * Class: Program #2 for CS 141, Fall 2017.  
 * Lab: Tues, 12pm
 * TA Minh  HuynhNguyen 
 * System: Mac OS X
 * Author: Lachezar Lyubenov
 */

#include <iostream>
#include <cctype>      // for toupper()
#include <string>
#include <stdio.h>
using namespace std;

#define NUMBER_OF_PIECES 36
#define ROW_SIZE 6

// Global variables and constants
char    p1, p2, p3, p4, p5, p6,
        p7, p8, p9,p10,p11,p12,
        p13,p14,p15,p16,p17,p18,
        p19,p20,p21,p22,p23,p24,
        p25,p26,p27,p28,p29,p30,
        p31,p32,p33,p34,p35,p36;

// Display ID info
void displayIDInfo()
{
    printf("Author:  Lachezar Lyubenov   \n");
    printf("Lab:     Tues, 12pm          \n");
    printf("Program: #2, Traffic \n");
    printf(" \n");
}//end displayIDInfo()

// Display Instructions
void displayInstructions()
{
    cout << "Welcome to the traffic game!                          " << endl
         << "                                                      " << endl
         << "Move the vehicles so that the Red car (RR) can exit   " << endl
         << "the board to the right. Each move should be of the    " << endl
         << "of the form:   CDN   where:                           " << endl
         << "   C  is the vehicle to be moved                      " << endl
         << "   D  is the direction (u=up, d=down, l=left or r=right)" << endl
         << "   N  is the number of squares to move it             " << endl
         << "For example GR2  means move the G vehicle to the right" << endl
         << "2 squares.  Lower-case input such as   gr2  is also   " << endl
         << "accepted.  Enter '-' to reset board, or 'x' to exit.  " << endl;
}

//setValue()
//set the piece at the piece index position to have 
//the indicated value.
void setValue( int pieceIndex, char& value)
{    
     // set the appropriate piece
     switch( pieceIndex) {
        case 1: p1 = value; break;        
        case 2: p2 = value; break;        
        case 3: p3 = value; break;        
        case 4: p4 = value; break;        
        case 5: p5 = value; break;        
        case 6: p6 = value; break;        
        case 7: p7 = value; break;        
        case 8: p8 = value; break;        
        case 9: p9 = value; break;        
        case 10: p10 = value; break;        
        case 11: p11 = value; break;        
        case 12: p12 = value; break;        
        case 13: p13 = value; break;        
        case 14: p14 = value; break;        
        case 15: p15 = value; break;        
        case 16: p16 = value; break;        
        case 17: p17 = value; break;        
        case 18: p18 = value; break;        
        case 19: p19 = value; break;        
        case 20: p20 = value; break; 
        case 21: p21 = value; break;        
        case 22: p22 = value; break;        
        case 23: p23 = value; break;        
        case 24: p24 = value; break;        
        case 25: p25 = value; break;        
        case 26: p26 = value; break;        
        case 27: p27 = value; break;        
        case 28: p28 = value; break;        
        case 29: p29 = value; break; 
        case 30: p30 = value; break;        
        case 31: p31 = value; break;        
        case 32: p32 = value; break;        
        case 33: p33 = value; break;        
        case 34: p34 = value; break;        
        case 35: p35 = value; break;        
        case 36: p36 = value; break;
        default: cout << "* ERROR * Invalid piece value chosen"; 
        
        break;        
     }   
}

//setValue( )
//Set the piece at position "row" and "column"
void setValue( int row, int column, char value)
{   
    // call the other version of setValue that expects to receive an int and a char
    int pieceIndex = (row-1)* ROW_SIZE + column;
    setValue( pieceIndex, value);   
}

//getValue()
//get the value of the piece at position "row" and "column" 
//This function takes this value from the appropriate piece 
char getValue( int row, int col) {

     char returnValue;
     int pieceIndex = (row-1)* ROW_SIZE + col;

     switch( pieceIndex) {
        case 1: returnValue = p1; break;        
        case 2: returnValue = p2; break;        
        case 3: returnValue = p3; break;        
        case 4: returnValue = p4; break;        
        case 5: returnValue = p5; break;        
        case 6: returnValue = p6; break;        
        case 7: returnValue = p7; break;        
        case 8: returnValue = p8; break;        
        case 9: returnValue = p9; break;        
        case 10: returnValue = p10; break;        
        case 11: returnValue = p11; break;        
        case 12: returnValue = p12; break;        
        case 13: returnValue = p13; break;        
        case 14: returnValue = p14; break;        
        case 15: returnValue = p15; break;        
        case 16: returnValue = p16; break;        
        case 17: returnValue = p17; break;        
        case 18: returnValue = p18; break;        
        case 19: returnValue = p19; break;        
        case 20: returnValue = p20; break; 
        case 21: returnValue = p21; break;        
        case 22: returnValue = p22; break;        
        case 23: returnValue = p23; break;        
        case 24: returnValue = p24; break;        
        case 25: returnValue = p25; break;        
        case 26: returnValue = p26; break;        
        case 27: returnValue = p27; break;        
        case 28: returnValue = p28; break;        
        case 29: returnValue = p29; break; 
        case 30: returnValue = p30; break;        
        case 31: returnValue = p31; break;        
        case 32: returnValue = p32; break;        
        case 33: returnValue = p33; break;        
        case 34: returnValue = p34; break;        
        case 35: returnValue = p35; break;        
        case 36: returnValue = p36; break;
        default: cout << "* ERROR * Invalid piece destination chosen"; break;   
     }   
     
     return returnValue;
}

//Index value for the chars.
int findMoveRow( char pieceIndex) {
    
    if (pieceIndex == p1 || pieceIndex == p2 || pieceIndex == p3 || pieceIndex == p4 || pieceIndex == p5 || pieceIndex == p6)
        return 1;
    else if (pieceIndex == p7 || pieceIndex == p8 || pieceIndex == p9 || pieceIndex == p10 || pieceIndex == p11 || pieceIndex == p12)
        return 2;
    else if (pieceIndex == p13 || pieceIndex == p14 || pieceIndex == p15 || pieceIndex == p16 || pieceIndex == p17 || pieceIndex == p18)
        return 3;
    else if (pieceIndex == p19 || pieceIndex == p20 || pieceIndex == p21 || pieceIndex == p22 || pieceIndex == p23 || pieceIndex == p24)
        return 4;
    else if (pieceIndex == p25 || pieceIndex == p26 || pieceIndex == p27 || pieceIndex == p28 || pieceIndex == p29 || pieceIndex == p30)
        return 5;
    else if (pieceIndex == p31 || pieceIndex == p32 || pieceIndex == p33 || pieceIndex == p34 || pieceIndex == p35 || pieceIndex == p36)
        return 6;    
}

//Index value for the chars.
int findMoveColumn (char pieceIndex) {
    
    if (pieceIndex == p1 || pieceIndex == p7 || pieceIndex == p13 || pieceIndex == p19 || pieceIndex == p25 || pieceIndex == p31)
        return 1;
    else if (pieceIndex == p2 || pieceIndex == p8 || pieceIndex == p14 || pieceIndex == p20 || pieceIndex == p26 || pieceIndex == p32)
        return 2;
    else if (pieceIndex == p3 || pieceIndex == p9 || pieceIndex == p15 || pieceIndex == p21 || pieceIndex == p27 || pieceIndex == p33)
        return 3;
    else if (pieceIndex == p4 || pieceIndex == p10 || pieceIndex == p16 || pieceIndex == p22 || pieceIndex == p28 || pieceIndex == p34)
        return 4;
    else if (pieceIndex == p5 || pieceIndex == p11 || pieceIndex == p17 || pieceIndex == p23 || pieceIndex == p29 || pieceIndex == p35)
        return 5;
    else if (pieceIndex == p6 || pieceIndex == p12 || pieceIndex == p18 || pieceIndex == p24 || pieceIndex == p30 || pieceIndex == p36)
        return 6;   
}

//Index value for the chars.
int findMoveRowUp( char pieceIndex) {

    if (pieceIndex == p31 || pieceIndex == p32 || pieceIndex == p33 || pieceIndex == p34 || pieceIndex == p35 || pieceIndex == p36)
        return 6;    
    else if (pieceIndex == p25 || pieceIndex == p26 || pieceIndex == p27 || pieceIndex == p28 || pieceIndex == p29 || pieceIndex == p30)
    	return 5; 
    else if (pieceIndex == p19 || pieceIndex == p20 || pieceIndex == p21 || pieceIndex == p22 || pieceIndex == p23 || pieceIndex == p24)
    	return 4;
    else if (pieceIndex == p13 || pieceIndex == p14 || pieceIndex == p15 || pieceIndex == p16 || pieceIndex == p17 || pieceIndex == p18)
    	return 3;
    else if (pieceIndex == p7 || pieceIndex == p8 || pieceIndex == p9 || pieceIndex == p10 || pieceIndex == p11 || pieceIndex == p12)
        return 2;
    else if (pieceIndex == p1 || pieceIndex == p2 || pieceIndex == p3 || pieceIndex == p4 || pieceIndex == p5 || pieceIndex == p6)
	return 1;
}

//Index value for the chars.
int findMoveColumnUp (char pieceIndex) {
    
    if (pieceIndex == p1 || pieceIndex == p7 || pieceIndex == p13 || pieceIndex == p19 || pieceIndex == p25 || pieceIndex == p31)
        return 6;
    else if (pieceIndex == p2 || pieceIndex == p8 || pieceIndex == p14 || pieceIndex == p20 || pieceIndex == p26 || pieceIndex == p32)
        return 5;
    else if (pieceIndex == p3 || pieceIndex == p9 || pieceIndex == p15 || pieceIndex == p21 || pieceIndex == p27 || pieceIndex == p33)
        return 4;
    else if (pieceIndex == p4 || pieceIndex == p10 || pieceIndex == p16 || pieceIndex == p22 || pieceIndex == p28 || pieceIndex == p34)
        return 3;
    else if (pieceIndex == p5 || pieceIndex == p11 || pieceIndex == p17 || pieceIndex == p23 || pieceIndex == p29 || pieceIndex == p35)
        return 2;
    else if (pieceIndex == p6 || pieceIndex == p12 || pieceIndex == p18 || pieceIndex == p24 || pieceIndex == p30 || pieceIndex == p36)
        return 1;   
}

//Function to display the board
void displayBoard( ) {
    
     // display column labels
     cout << "  -------------------------" << endl;
     
     // for each row
     for ( int row=1; row<=ROW_SIZE; row++) {
         cout << " | ";
         
         // for each column
         for( int col=1; col<=ROW_SIZE; col++) {
            cout << getValue(row, col) << " | ";      
         }
         cout << endl;
         cout << "  -------------------------" << endl;
     }
}

//-----------------------------------------------------------
// gameNotFinished()
//		see if the game is finished, by checking the number of squares that
//      have been filled in on the board.
//  
bool gameNotFinished( char p18) {
    
    if( p18 == 'R') {
        return false;   // game IS finished
    }   
    else {
        return true;    // game is NOT yet finished
    }
}

//Function to Move car to the right
void moveRowRight(string _input){
    char s = toupper(_input.at(0));
    
    int row = findMoveRow(s);
    int column = findMoveColumn(s);
    char moves = _input.at(2); 
    int ia = moves - '0'; 
    int count = 0;
    
    for ( int i=column + 1; i<=ROW_SIZE; i++) {
  	char v = getValue(row,i);
	if (count < ia && v != '.' && v != s) {
	    cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
	    return;
	    }
	if (count < ia && v == '.'){
	    count = count + 1;
        setValue(row,i,s);	
	    setValue(row,findMoveColumn(s),'.');
	    }		
    } 
} 

//Function to move car to the left
void moveRowLeft(string _input){
    char s = toupper(_input.at(0));
    
    int row = findMoveRowUp(s);
    int column = findMoveColumn(s);
    char moves = _input.at(2); 
    int ia = moves - '0'; 
    int count = 0;
    for ( int i= findMoveColumn(s); i>0; i--) {
  	char v = getValue(row, i);
  	if (count < ia && v != '.' && v != s)
	{
	  cout << "*** Move was attempted, but couldn't be completed. ***" <<endl; 
	 return;
	}
	if (count < ia && v == '.'){
	   count = count + 1;
           setValue(row, i,s);	
	   setValue(row, findMoveRow(s),'.');
	}		
    } 
}

//Function to move car down
void moveColumnDown(string _input){
    char s = toupper(_input.at(0));
    
    int row = findMoveRow(s);
    int column = findMoveColumn(s);
    char moves = _input.at(2); 
    int ia = moves - '0'; 
    int count = 0;
    
    for ( int i=row +1 ; i<=ROW_SIZE; i++) {
  	    char v = getValue(i,column);
	if (count < ia && v != '.' && v != s) {
	    cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
	  return;
	}
	if (count < ia && v == '.'){
	    count = count + 1;
        setValue(i,column,s);	
	    setValue(row,findMoveColumn(s),'.');
        }		
    } 
} 

//Function to move the car up.
void moveRowUp(string _input){
    char s = toupper(_input.at(0));
    
    int row = findMoveRowUp(s);
    int column = findMoveColumn(s);
    char moves = _input.at(2); 
    int ia = moves - '0'; 
    int count = 0;
    
    for ( int i= findMoveRow(s); i>0; i--) {
  	char v = getValue(i,column);
  	    if (count < ia && v != '.' && v != s) {
  	        cout << "*** Move was attempted, but couldn't be completed. ***" <<endl; 
	        return;
	    }
	    if (count < ia && v == '.'){
	        count = count + 1;
            setValue(i, column,s);	
	        setValue(column, findMoveColumn(s),'.');
	    }		
    } 
}

//Main Function
int main()
{
    // Declare your variables here
    string str;
    char row, col, value;
    
    displayIDInfo();        // Display ID info
    displayInstructions();  // Display game instructions
    
    // Set the board values
    p1='G'; p2='G'; p3='.'; p4='.'; p5='.'; p6='Y';
    p7='P'; p8='.'; p9='.';p10='B';p11='.';p12='Y';
    p13='P';p14='R';p15='R';p16='B';p17='.';p18='Y';
    p19='P';p20='.';p21='.';p22='B';p23='.';p24='.';
    p25='O';p26='.';p27='.';p28='.';p29='T';p30='T';
    p31='O';p32='.';p33='F';p34='F';p35='F';p36='.';

    // Main While Loop for game.
    while (gameNotFinished) {
        
        displayBoard();
	    // Prompt for user input.  Handle 'x' for exit
		cout << "Your move -> ";
		cin >> str;
		if (str.at(0) == 'x' || str.at(0) == 'X') {
		    cout << "The exit option was selected. \n"
				 << "\n";
			break;		// exit was chosen, so exit program
		}
		if ( toupper(str.at(1)) == 'R') {
                moveRowRight(str);
	        }
        if ( toupper(str.at(1)) == 'L') {
                moveRowLeft(str);
            }
        if ( toupper(str.at(1)) == 'D') {
                moveColumnDown(str);
            }
        if ( toupper(str.at(1)) == 'U') {
                moveRowUp(str);
            }    
	    }
    cout << endl;
    cout << "Thank you for playing.  Exiting..." << endl;

    return 0;
}//end main()



