//------------------------------------------------------------------------------
 /* The program guesses the user's number.
    The user chooses a number (for example 45) then subtracts the two digits:
    (49 - 4 - 9 = 36).
    The user needs to remember the letter next to the new number, then computer
    predicts the letter of the new number.
    
    Class: CS 141, Fall 2017
    Author: Lachezar Lyubenov
    Lab: Moumita Samanta - Tues 12pm
    Date: Aug 29, 2017
    System:  C++ in Cloud 9
 */
//------------------------------------------------------------------------------
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

// Main() function for the program
//------------------------------------------------------------------------------

int main()
{
    //Declaring variables
    char randomChar;       //Stores the random generated letters
    char mysteryLetter;     //Stores the "computer guessed" letter
	int randomNumber = 0;   //Stores the random numbers 
	srand(time(0));         //Randomizes the generated numbers.
	
	//Program title and identifying information
    cout << "Program #1: Guess It" << endl;
    cout << "Author: Lachezar Lyubenov" << endl;
    cout << "Lab: Moumita Samanta - Tues 12pm" << endl;
    cout << "Date: Aug 29, 2017" << endl;
    cout << "System:  C++ in Cloud 9" << endl;
    cout << endl; 
    
    //While Loop to set the letters to Upper or Lower each character
    while (randomNumber = rand()%26) {
        if (randomNumber%2 == 0) {
            randomChar = 'A' + randomNumber;    
        }
        else {
            randomChar = 'a' + randomNumber;            
        }
    }
    
    //Determines the Special Character
    int lettersUpLow = (rand() %2) + 1;
    if (lettersUpLow == 2) {
        mysteryLetter = (rand() %26) + 65;
    }
        else if (lettersUpLow == 1) {
            mysteryLetter = (rand() %26) + 97;
        }
        
    //While loop that creates the table, assigns which values are Lower and Upper characters, and the special character
    int countdown = 99;
    while (countdown >= 0) {
            randomNumber = rand()%26;                   //Finds random number from 0 - 25
                cout << setw(3) << countdown << ":";
            //If counter is multiple of 9 - insert the randomly selected "mysteryLetter"
            if (countdown %9 == 0)  {
                cout << mysteryLetter;
            }
            //Else, insert randomly generated randomChar alphabet characters
            else {
                if (randomNumber %2 == 0) {
                    randomChar = 'A' + randomNumber;   //Creates new Upper Character
                    cout << randomChar;
                }
                else {
                    randomChar = 'a' + randomNumber;   //Create new Lower Character    
                    cout << randomChar;
                }
            }
            //Go to new line if we are at even multiple of 10 (line up the table)
            if (countdown %10 == 0) {
                cout << endl;  
            }
             
            countdown--;
        } //End of main while loop
        
    //Displays user instructions
    cout << "\n" << "\n";
    cout << "1. Choose any two-digit number in the table above (e.g. 73)." << endl;
    cout << "2. Subtract its two digits from itself (e.g. 73 - 7 - 3 = 63)." << endl;
    cout << "3. Find this new number (e.g. 63) and remember the letter next to it." << endl;
    cout << "4. Now press 'r' and I'll read your mind...";
    
    //Displays the computer generated special character
    while(cin.get() != '\n') {
    cout << "You selected the character: " << mysteryLetter;
    }
    
   return 0;
} //End of main()