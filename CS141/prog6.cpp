/* steiner.cpp
 *  Graphics demo program for getting started with QtCreator for program 6, Steiner Trees.
 *
 * Author: Lachezar Lyubenov
 * Date: 12/05/17
 * Class: CS 141, Fall 2017
 * System: QtCreator with Stanford graphics library, on iMac, OS Sierra
 *
 */

#include <iostream>
#include "gobjects.h"  // for all graphics objects
#include "gevents.h"   // for mouse events
#include <fstream>        // For file input
#include <cmath>
#include <ctime>
using namespace std;

// Global constants
const int PointRadius = 7;

// Create a graphics window, which will be used to draw graphical shapes.
GWindow graphicsWindow;

//------------------------------------------------------------------------------------------
// Class to draw points (circles)
class MyPoint {
private:
    int x, y;
    string color;

public:
    void setPoints(int x, int y, string fill);
    MyPoint(){}
    MyPoint (int x, int y, string fill) {
        setPoints (x, y, fill);
    };

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }
};

//------------------------------------------------------------------------------------------
// Function that sets points based on the information passed from the vector
void MyPoint::setPoints(int xCord, int yCord, string fill)
{
    this->color = fill;
    this->x = xCord;
    this->y = yCord;

    GOval *pTheOval = new GOval( x-PointRadius, y-PointRadius, PointRadius*2, PointRadius*2);
    pTheOval->setFilled( true);
    pTheOval->setColor( fill);
    graphicsWindow.add( pTheOval);
}//end setPoints()

//------------------------------------------------------------------------------------------
// Class to draw buttons
class MyButton {
private:
    int x, y, width, height;
    string color, fill, text;
    GRect * theRectangle;
    GLabel * theLabel;
public:
    void setButton(int x, int y, int width, int height, string fill, string text);
    MyButton(){}
    MyButton (int x, int y, int width, int height, string fill, string text) {
        setButton (x, y, width, height, fill, text);
    };
    GRect* getRectangle();

    bool clickedOn(int mouseX, int mouseY);
};

//------------------------------------------------------------------------------------------
//Function that checks if a button has been clicked based on mouse coordinates
bool MyButton::clickedOn(int mouseX, int mouseY)
{
    return MyButton::getRectangle()->contains( mouseX, mouseY);
}//end clickedOn()

//------------------------------------------------------------------------------------------
//Function of GRect that returns theRectangle
GRect* MyButton::getRectangle()
{
    return theRectangle;
}//end getRectangle()

//------------------------------------------------------------------------------------------
//Function that sets the buttons based on the data provided by professor Reed
void MyButton::setButton(int buttonX, int buttonY, int buttonWidth, int buttonHeight, string fill, string word)
{
    this->x = buttonX;
    this->y = buttonY;
    this->width = buttonWidth;
    this->height = buttonHeight;
    this->color = fill;
    this->text = word;
    theRectangle = new GRect(buttonX, buttonY, buttonWidth, buttonHeight);
    theRectangle->setColor( color);
    theRectangle->setFilled( true);
    graphicsWindow.add( theRectangle);

    theLabel = new GLabel( text);
    int xOffset = (buttonWidth  - theLabel->getBounds().getWidth()) / 2;
    int yOffset = (buttonHeight - theLabel->getBounds().getHeight()) + 5;
    theLabel->setLocation( buttonX + xOffset, buttonY + yOffset);
    graphicsWindow.add( theLabel);
}//end setButton()

//------------------------------------------------------------------------------------------
// Class to draw lines
class MyLine {
private:
    double startX, startY, endX, endY;

public:
    void setLine(int x, int y, int endX, int endY);
    MyLine(){}
    MyLine (int x, int y, int endX, int endY) {
        setLine (x, y, endX, endY);
    };
    int getStartX();
    int getStartY();
    int getEndX();
    int getEndY();
};

// Getter for starting x value
int MyLine::getStartX(){
    return startX;
}//end getStartX()

// Getter for starting y value
int MyLine::getStartY(){
    return this->startY;
}//end getStartY()

// Getter for end x value
int MyLine::getEndX(){
    return this->endX;
}//end getEndX()

// Getter for end y value
int MyLine::getEndY(){
    return this->endY;
}//end getEndY()

//------------------------------------------------------------------------------------------
// Function that sets the lines
void MyLine::setLine( int begX, int begY, int finX, int finY)
{
    this->startX = begX;
    this->startY = begY;
    this->endX = finX;
    this->endY = finY;
}//end setLine()

//------------------------------------------------------------------------------------------
// Read in the sets of points information from the data file
void readInputFile( vector<MyPoint> &pointsArray, int &idealScore)
{
    ifstream inputFileStream;  // declare the input file stream

    // Open input file and verify.
    inputFileStream.open("data.txt");
    if( !inputFileStream.is_open()) {
        cout << "Could not find input file data.txt.  Exiting..." << endl;
        exit( -1);
    }

    // Read sets of data from input file.  Each read operation reads the next set of data.
    int whichSetToUse;
    inputFileStream >> whichSetToUse;

    int howManyPoints;    // How many points are in the set of points
    int x, y;             // Store individual point x,y values from input file

    // Read in and discard some number of sets of points before we get the real set we will be using
    for( int i = 0; i < whichSetToUse-1; i++) {
        inputFileStream >> howManyPoints >> idealScore;
        for( int j = 0; j < howManyPoints; j++) {
            inputFileStream >> x >> y;    // Read in the points
        }
    }

    inputFileStream >> howManyPoints >> idealScore;

    // Read in and store the points information
    for( int i = 0; i < howManyPoints; i++) {
        inputFileStream >> x >> y;    // Read in the points

        // Store the points in a vector
        MyPoint *newPoint = new MyPoint(x, y, "black");
        pointsArray.push_back( *newPoint);
        free(newPoint);
    }
}//end readInputFile()

//------------------------------------------------------------------------------------------
// Function that calculates the distance of the drawn lines
int calcDistance (vector<MyLine> my_lines)
{
    int total = 0;
    for (vector<MyLine>::iterator it= my_lines.begin(); it !=my_lines.end(); ++it) {
        int diffx = abs(it->getStartX()-it->getEndX());
        int diffy = abs(it->getStartY()-it->getEndY());
        int length = sqrt(  diffx*diffx + diffy*diffy);
        total +=length;
    }
    return total;
}//end calcDistance()

//------------------------------------------------------------------------------------------
// Function that calculates that line that is currently being created
int calcCurrentLenght(int startX, int startY, int mouseX, int mouseY, int total)
{
    int currentLine = hypot(startX - mouseX, startY - mouseY);
    int currentTotal = currentLine + total;
    return currentTotal;
}//end calcCurrentLength

//------------------------------------------------------------------------------------------
// Function that snaps the lines into the closest points (circles)
void getNearestPoints(vector<MyPoint> &pointsArray, int &mouseX, int &mouseY)
{
    int minLength = hypot(pointsArray.at(0).getX() - mouseX, pointsArray.at(0).getY() - mouseY);
    int minIndex = 0;
    for(int i = 0; i < pointsArray.size(); i++)
    {
        int tempLength = hypot(pointsArray.at(i).getX() - mouseX, pointsArray.at(i).getY() - mouseY);
        if(tempLength < minLength)
        {
            minLength = tempLength;
            minIndex = i;
        }
    }
    mouseX = pointsArray.at(minIndex).getX();
    mouseY = pointsArray.at(minIndex).getY();
}//end getNearestPoints

//------------------------------------------------------------------------------------------
// Main
int main()
{
    graphicsWindow.setCanvasSize( 400, 400);   // Set the size
    graphicsWindow.setWindowTitle("  llyube2  QtCreator Program 6");

    vector<MyPoint> pointsArray;    // Store all points that are created.
    vector<MyLine> my_lines;        // Store all GLine * lines

    int idealScore = 0;             // Precomputed ideal score for each puzzle

    // Get the set of data to use from the input file
    readInputFile( pointsArray, idealScore);

    // Create the Control and message components.
    // Messages label at the top of the window
    GLabel *messagesLabel = new GLabel();
    messagesLabel->setText("Find the minimal spanning tree, using additional points.");
    messagesLabel->setLocation( 30,20);
    graphicsWindow.add( messagesLabel);  // Push the label to the top of the Graphics Window

    MyButton *exitButton = new MyButton(250, 350, 50, 30, "red", "Exit");
    MyButton *addPoints = new MyButton(10, 350, 70, 30, "green", "Add Points");
    MyButton *addLines = new MyButton(90, 350, 70, 30, "lightgray", "Draw Lines");

    // Make the graphics window have focus, since all interaction will be through the window
    graphicsWindow.requestFocus();

    // Set values to use for keeping track of program modes
    const int Default = 0;
    const int DrawPoints = 1;
    const int DrawLines = 2;
    int programMode = Default;  // Modes are Default, DrawPoints, DrawLines.  Program starts in Default mode
                                // Change to the other modes when those buttons are pressed.
    bool buttonWasPressed = false;    // Set to false when a button is pressed.  Used to avoid drawing on buttons

    int mouseX = -1;                    // Will store mouse position X
    int mouseY = -1;                    // Will store mouse position Y
    char message[ 81];                  // Used to construct message to be displayed at top of window


    GMouseEvent e;      // Stores the mouse event each time through the event loop
    GLine *pLine;

    GLabel *firstBottomLabel = new GLabel();            // First bottom Label being initiated with text
    firstBottomLabel->setText("Distance is: ");
    firstBottomLabel->setLocation( 310,360);
    graphicsWindow.add( firstBottomLabel);

    GLabel *secondBottomLabel = new GLabel();           // Second bottom Label being initiated with text
    secondBottomLabel->setText("0 ");
    secondBottomLabel->setLocation( 330,380);
    graphicsWindow.add( secondBottomLabel);

    // Main event loop - divided in MOUSE_PRESSED, MOUSE_RELEASED and MOUSE_DRAGGED
    while (true) {

        // Wait for a mouse event, then get the x,y coordinates
        e = waitForEvent(MOUSE_EVENT);

        // Get the current mouse x,y location
        mouseX = e.getX();
        mouseY = e.getY();

        //  -------- Perform actions for different kinds of mouse events --------
        if (e.getEventType() == MOUSE_PRESSED) {
            // See if Exit button was clicked by seeing if mouse press location is inside the rectangle
            if( exitButton->getRectangle()->contains( mouseX, mouseY) ) {
                messagesLabel->setLabel("Exiting...");
                break;
            }
            // Check to see if button to draw points has been clicked
            else if (addPoints->getRectangle()->contains(mouseX, mouseY)) {
                buttonWasPressed = true;
                messagesLabel->setLabel("Click to add points.");
                programMode = DrawPoints;
            }
            // Check to see if button to draw lines has been clicked
            else if (addLines->getRectangle()->contains(mouseX, mouseY))
            {
                buttonWasPressed = true;
                programMode = DrawLines;
                messagesLabel->setLabel("Click and drag between two points to draw lines.");
            }
            // If DrawLines button has been clicked -> create the line from the nearest point that a click originated from
            else if ((programMode == DrawLines) && (buttonWasPressed == false))
            {
                getNearestPoints( pointsArray, mouseX, mouseY);
                pLine = new GLine (mouseX, mouseY, mouseX, mouseY);
                sprintf( message,"Setting line starting point to %d, %d", mouseX, mouseY);  // print into a string
                messagesLabel->setLabel(message);
                pLine->setLineWidth(2);
                graphicsWindow.add(pLine);
            }
            // If DrawPoints button has been clicked -> set the point based on the location of the mouse click
            else if ((programMode == DrawPoints) && (buttonWasPressed == false))
            {
                MyPoint *newPoint = new MyPoint(mouseX, mouseY, "blue");
                pointsArray.push_back( *newPoint);
            }
        }
        else if( e.getEventType() == MOUSE_RELEASED) {
            // Set the end point of the previously created line that currently has the same begin & end points
            if (programMode == DrawLines && buttonWasPressed == false){
                int xValue = pLine->getStartPoint().getX();
                int yValue = pLine->getStartPoint().getY();
                getNearestPoints( pointsArray, mouseX, mouseY);
                pLine->setEndPoint(mouseX, mouseY);
                MyLine *ml = new MyLine(xValue,yValue,mouseX,mouseY);
                my_lines.push_back(*ml);

                // Statement that calculates the total length of all lines that are created and checks for a win/lose
                int lineTotals = calcDistance (my_lines);
                if (lineTotals < 1.05*idealScore )
                {
                    sprintf( message,"Yes! %d is less or close to goal of %d", lineTotals, idealScore);  // Displays winning message on top of graphics window
                    messagesLabel->setLabel(message);
                }
                else{
                    sprintf( message,"Sorry ! %d is larger than %d", lineTotals, idealScore);  // Displays losing message on top of graphics window
                    messagesLabel->setLabel(message);
                }
                sprintf( message,"%d", lineTotals);  // Print the Line's Distance on the bottom of the graphics window
                secondBottomLabel->setLabel(message);
            }
            buttonWasPressed = false; // Sets buttonWasPressed to false again
        }
        else if(e.getEventType() == MOUSE_DRAGGED) {
            // If statement that displays the line that is currently being drawn and calculates dynamically the length of line being created
            if (programMode == DrawLines && buttonWasPressed != true)
            {
                int startX = pLine->getStartPoint().getX();
                int startY = pLine->getStartPoint().getY();
                pLine->setEndPoint(mouseX, mouseY);
                int currentLength = calcCurrentLenght(startX, startY, mouseX, mouseY, calcDistance (my_lines));
                sprintf( message,"%d", currentLength);  // Print the Line's Distance on the bottom of the graphics window
                secondBottomLabel->setLabel(message);
            }
        }
    }//end while( true)

    // Close the windows, first the graphics window
    graphicsWindow.requestFocus();
    graphicsWindow.close();
    exitGraphics();

    return 0;
}
