/* --------------------------------------------------------
 * Traffic.cpp
 *     Graphics-based version of the game RushHour, where the
 *     object is to move the vehicles such that the small
 *     car can exit the right of the board.
 *
 *
 *
 * This program heavily relies on pointers as a means to iterate through memory addresses
 * I used dereferencing to access each location and swap values. Pointers seemed to be an
 * easier way to finish the assignment without creating too many variables. This assignment gave
 *.me a much better grasp of how to use pointers and of their powerful utlility.
 *
 * Class: Program #4 for CS 141, Fall 2017.
 * Lab: 12pm Lamar
 * TA Moumita Samanta
 * System:Windows 10/Mac OS
 * Author: Lachezar Lyubenov
 */

#include <fstream>
#include <iostream>
#include "gobjects.h"   // For the Stanford graphics library
#include <fstream>      // For file input
#include <cstring>      // For string functions
#define DEFAULT 8
#define LENGTH 6

using namespace std;

class Cars {
  public:
    void setInfo(char color, char direction, int xPos, int yPos, int size);

    char fill, type;
    int xCord, yCord, length;

};

void Cars::setInfo(char color, char direction, int xPos, int yPos, int size)
{
    fill = color;
    type = direction;
    xCord = xPos;
    yCord = yPos;
    length = size;

}
// Display ID info
void displayIDInfo()
{
    cout << "Author:  Narayan Guerrero, Lachezar Lyubenov" << endl;
    cout << "Lab: 12pm Lamar" 			<< endl;
    cout << "Program: #4, Traffic" 		<< endl;
    cout << endl;
}
//--------------------------------------------------------------------

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
         << "   N  is the number of squares to move it             " << endl           << "For example GR2  means move the G vehicle to the right" << endl
         << "2 squares.  Lower-case input such as   gr2  is also   " << endl
         << "accepted.  Enter \"reset\" to reset board, or \"exit\" to exit.  " << endl;
}

// Function to zero out the board
void eraseTable(char table[LENGTH][LENGTH])
{
    for (int row = 0; row < LENGTH; row++) {
        for (int col = 0; col < LENGTH; col++)
        {
            table[row][col] = '.';
        }
    }
}

// Function to start the game with default board from text file
void startCars(vector<Cars>& myCar, char table[LENGTH][LENGTH])
{

    // Declared variables for populating information into vector and array
    ifstream file;
    int numCars;
    char color, direction;
    int rowPos, colPos, size = 0;

    file.open("board.txt");                                                     //File used for game data
    file >> numCars;

    //blankCars(numCars);

    for (int i = 0; i < numCars; ++i)                                           //Loop sets data from file to cars
    {
        file >> color >> direction >> rowPos >> colPos >> size;
        myCar.at(i).setInfo(color, direction, rowPos, colPos, size);
        table[rowPos-1][colPos-1] = color;
        if ((direction == 'H') && (size == 2)) {table[rowPos-1][colPos] = color;}
        if ((direction == 'H') && (size == 3)) {table[rowPos-1][colPos] = color; table[rowPos-1][colPos+1] = color;}
        if ((direction == 'V') && (size == 2)) {table[rowPos-1][colPos+5] = color;}
        if ((direction == 'V') && (size == 3)) {table[rowPos-1][colPos+5] = color; table[rowPos-1][colPos+11] = color;}
    }

}

//Function that draws the background board for cars to move on
void drawTheBoard(GWindow myWindow) {

    GRect *board1 = new GRect(10, 10, 270, 270); board1->setFilled(true); board1->setColor("darkGray");
    myWindow.add(board1);

    //Inner Playing Surface
    GRect *board2 = new GRect(20, 20, 250, 250); board2->setFilled(true); board2->setColor("gray");
    myWindow.add(board2);

    //Exit Opening
    GRect *board3 = new GRect(270, 100, 10, 50); board3->setFilled(true); board3->setColor("lightGray");
    myWindow.add(board3);

    //Vertical Lines
    GRect *board4 = new GRect(20, 20, 10, 250); board4->setFilled(true); board4->setColor("lightGray");
    myWindow.add(board4);
    GRect *board5 = new GRect(60, 20, 10, 250); board5->setFilled(true); board5->setColor("lightGray");
    myWindow.add(board5);
    GRect *board6 = new GRect(100, 20, 10, 250); board6->setFilled(true); board6->setColor("lightGray");
    myWindow.add(board6);
    GRect *board7 = new GRect(140, 20, 10, 250); board7->setFilled(true); board7->setColor("lightGray");
    myWindow.add(board7);
    GRect *board8 = new GRect(180, 20, 10, 250); board8->setFilled(true); board8->setColor("lightGray");
    myWindow.add(board8);
    GRect *board9 = new GRect(220, 20, 10, 250); board9->setFilled(true); board9->setColor("lightGray");
    myWindow.add(board9);
    GRect *board10 = new GRect(260, 20, 10, 250); board10->setFilled(true); board10->setColor("lightGray");
    myWindow.add(board10);

    //Horizontal Lines
    GRect *board11 = new GRect(20, 20, 250, 10); board11->setFilled(true); board11->setColor("lightGray");
    myWindow.add(board11);
    GRect *board12 = new GRect(20, 60, 250, 10); board12->setFilled(true); board12->setColor("lightGray");
    myWindow.add(board12);
    GRect *board13 = new GRect(20, 100, 250, 10); board13->setFilled(true); board13->setColor("lightGray");
    myWindow.add(board13);
    GRect *board14 = new GRect(20, 140, 250, 10); board14->setFilled(true); board14->setColor("lightGray");
    myWindow.add(board14);
    GRect *board15 = new GRect(20, 180, 250, 10); board15->setFilled(true); board15->setColor("lightGray");
    myWindow.add(board15);
    GRect *board16 = new GRect(20, 220, 250, 10); board16->setFilled(true); board16->setColor("lightGray");
    myWindow.add(board16);
    GRect *board17 = new GRect(20, 260, 250, 10); board17->setFilled(true); board17->setColor("lightGray");
    myWindow.add(board17);
}

//Function that finds different sizes for different cars
int findSize (char table[][LENGTH], char letter)
{
    int size = 0;
    for (int row = 0; row < LENGTH; row ++)
    {
        for (int col = 0; col < LENGTH; col++){
            if (table[row][col] == letter) {size += 1;}
        }
    }
    return size - 1;
}

//Function that changes the 2D array for car limits/checking for overlap
void changeTable (char table[][LENGTH], char direction, char letter)
{
    int size = findSize(table, letter);

    if (direction == 'U')
    {
    for (int row = 0; row < LENGTH; row++)
        {
            for (int col = 0; col < LENGTH; col ++)
            {
                if (table[row][col] == letter && (table[row-1][col] == '.'))
                {
                    table[row + size][col] = '.';
                    table[row - 1][col] = table[row][col];
                }
            }
        }
    }
    if (direction == 'D')
    {
    for (int row = 0; row < LENGTH; row++)
        {
            for (int col = 0; col < LENGTH; col ++)
            {
                if (table[row][col] == letter)
                {

                }
            }
        }
    }
    cout << letter << " : " << size << endl;
}

void errorCheck(char myTable[][LENGTH], char direction, char letter, char travel)
{

}

//Function to check for win
bool checkWin (char table[][LENGTH])
{
    if (table[2][5] == 'R') {

        cout << "Congratulations you won!" << endl;
        return true;
    }
    return true;
}

//Function that populates cars with unique information per car
void populateCars(Cars car, int &findPosX, int &findPosY, int &drawPosX, int &drawPosY, string &fillMe)
{
   // Cars objCar;
    if (car.type == 'H')
    {
        findPosY = (car.xCord * 30) + (car.xCord - 1) * 10;
        findPosX = (car.yCord * 30) + (car.yCord - 1) * 10;
        drawPosX = (car.length * 30) + (car.length -1) * 10;
        drawPosY = 30;
    }
    else if (car.type == 'V')
    {
        findPosY = (car.xCord * 30) + (car.xCord - 1) * 10;
        findPosX = (car.yCord * 30) + (car.yCord - 1) * 10;
        drawPosX = 30;
        drawPosY = (car.length * 30) + (car.length -1) * 10;
    }
        switch (car.fill)
        {
        case ('G') : fillMe = "green"; break;
        case ('Y') : fillMe = "yellow"; break;
        case ('M') : fillMe = "magenta"; break;
        case ('R') : fillMe = "red"; break;
        case ('B') : fillMe = "blue"; break;
        case ('O') : fillMe = "orange"; break;
        case ('C') : fillMe = "cyan"; break;
        case ('P') : fillMe = "pink"; break;
        }
 }

// Function that moves Vehicles based on user input/type/size
void moveCar(char myTable[][LENGTH], GRect* carGraphic, Cars car, char direction, char travel)
{
    char test;
    int foundX, foundY, makeX, makeY;
    travel = travel - '0';
    if (car.type == 'V'){

        if ((direction == 'U') || (direction == 'D')) {
            if (direction == 'U')
            {
                changeTable(myTable,direction, car.fill);
                carGraphic->move(0,(-40*travel));
            }
            if (direction == 'D')
            {
                changeTable(myTable,direction, car.fill);
                carGraphic->move(0,(40*travel));
            }
        }
        else {cout << "Attempt was made to move a piece in the wrong direction.  Please retry." << endl;}
    }
    if (car.type == 'H') {
        if ((direction == 'R') || (direction == 'L')) {
            if (direction == 'R') {carGraphic->move((40*travel),0);}
            if (direction == 'L') {carGraphic->move((-40*travel),0);}

        }
        else {cout << "Attempt was made to move a piece in the wrong direction.  Please retry." << endl;}
    }
}

//Function used to debug 2D array in background - Erase on completion
void displayBoard(char myTable[][LENGTH])
{
    for (int oneDimension = 0; oneDimension < 6; oneDimension++)
    {
        for (int anotherDimension = 0; anotherDimension < 6; anotherDimension++)
        {
            cout << myTable[oneDimension][anotherDimension];
        }
        cout << endl;
    }
}

//Main Function of the program
int main () {

    //Declared variables

    string userInput;
    int moveNumber = 0;

    // Board set up for game start
    GWindow myWindow(300,300);
    myWindow.setWindowTitle("CS 141: Prog 4 Graphical Traffic");
    myWindow.setExitOnClose( true);
    drawTheBoard( myWindow);

    // Arrays and vector start up for populating the cars
    char myTable[LENGTH][LENGTH];                                   //Used for Error Checking  and limits
    eraseTable(myTable);
    vector<Cars> cars(DEFAULT);                                     //Used for car information

    startCars(cars, myTable);                                       //Default Car placement
    GRect* garage[8];                                               //Game cars for playing with updated info

    string pigment;
    int foundX = 0, foundY = 0, makeX = 0, makeY = 0;

    for (int i = 0; i < DEFAULT; i++)
    {
        garage[i] = new GRect(0, 0, 0, 0); garage[i]->setFilled(true); garage[i]->setColor("black");
        populateCars(cars.at(i),foundX, foundY, makeX, makeY, pigment);
        garage[i]->setBounds(foundX,foundY,makeX,makeY); myWindow.add(garage[i]); garage[i]->setColor(pigment);
    }

    displayIDInfo();        // Display ID info
    displayInstructions();  // Display game instructions

    do
    {
        cout << moveNumber++ << ". Your move -> ";
        getline(cin, userInput);

        for (int i = 0; i < userInput.length(); i++)
            userInput[i] = toupper(userInput[i]);
        if (userInput == "EXIT")
            break;
        if (userInput == "RESET"){}

        for (int j = 0; j < DEFAULT; j++)
        {
            if (userInput[0] == cars[j].fill)
            {

                moveCar(myTable, garage[j], cars.at(j), userInput[1], userInput[2]);
                break;
            }
            if ((j + 1) == DEFAULT)
                cout << "User input is not one of the valid color or action items.  Please retry." << endl;
        }


    } while (true);

    myWindow.close();
    exitGraphics();
    return 0;
}
