#ifndef CREATURE_H
#define CREATURE_H

#include <cstdlib>
#include <ctime>

#include "GridDisplay.h"

class Island;
class Creature;

class Creature
{
 protected:
   Island* isl;
   int row;
   int col;
   int breedDaysPassed;
   char bugType;


  //friend class Island;
 public:
   Creature();
   //Creature(Island *island, GridDisplay *grid);
   Creature(Island *island, int row, int col);
   virtual ~Creature();
   virtual void move();
   virtual void breed();
   virtual void hunt();   

   char setBugType(char type);
   char getBugType();
   bool moved;

};

class Island
{
 private:
   Creature* **location;  // Dynamic 2D array of pointers
   GridDisplay *gd;
   int rows;
   int cols;

 public:
   Island(GridDisplay *grid);
   ~Island(){};
   Island* getLocation(int r, int c);
   void resetCreatures();
   void dailyRoutine();
   void moveCreatures();
   void checkForDeath();
   void checkForBreeding();
   void feedTheBuggers();
   //void dayStart();
   Creature *getBug(int r, int c);


   int getRows();
   int getCols();
   bool isValid (int r, int c);
   bool isOccupied (int r, int c);
   bool addCreature (Creature* b, int r, int c);
   bool moveCreature (int currX, int currY, int nextX, int nextY);
   void deleteBug (int r, int c);
};


#endif