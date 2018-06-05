//Program 6 - CS 211
//Lachezar Lyubenov - llyube2

#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cstring>


#include "GridDisplay.h"
#include "Creature.h"

//Main function
int main ( int argc, char** argv)
{
 int delay =1000;
 int day = 0;

for (int i = 0; i < argc; i++)
{
  if(strcmp(argv[i], "-d") == 0)
  {
    delay = sscanf(argv[i], "%i", &delay);
  }
}
  
 GridDisplay gd;
 Island island(&gd);
 //Creature;

 //gd.showGrid();
 // loop for 20 days
 while ( day < 20 )
 {
    day++;
    island.dailyRoutine();
    //island.dayStart();
    // pause execution to allow "animation" to be seen
    gd.mySleep( delay );
    gd.showGrid();
 }

}

