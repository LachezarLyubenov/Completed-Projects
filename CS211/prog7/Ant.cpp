//Ant Class
#include "Ant.h"
#include "Creature.h"

//constructor
Ant::Ant(Island *island, int row, int col) : Creature(island, row, col)
{
    bugType = 'a';
}

//virtual move
void Ant::move()
  {
    int direction[4] = {0, 1, 2 ,3};
    int tempD;
    int swapTemp;
    for (int k = 0; k < 4; k++)
    {
        srand(time(NULL));
        tempD = rand() % 4;
        swapTemp = direction[k];
        direction[k] = direction[tempD];
        direction[tempD] = swapTemp;
    }
        srand(time(NULL));
        tempD = rand() % 4;
    for(int i = 0; i < 4; i++)
    {
      //printf("direction[i]: %d, i: %d", direction[i], i);
    if ( direction[i] == 0 ) // attempt to move left
    {
        if((col>0) && isl->isOccupied(row, col-1) == false)
        {

            isl->moveCreature ( row, col, row, col-1 );
            moved = true;
            break;
        }
    }
    else if ( direction[i] == 1 ) // attempt to move right
    {
        if((col > isl->getCols()-1) && isl->isOccupied(row, col+1) == false)
        {

            isl->moveCreature ( row, col, row, col+1 );
            moved = true;
            break;
        }
    }
    else if ( direction[i] == 2 ) // attempt to move up
    {
        if((row>0) && isl->isOccupied(row-1, col) == false)
        {
            isl->moveCreature ( row, col, row-1, col );
            moved = true;
            break;
        }
    }
    else if ( direction[i] == 3 ) // attempt to move down
    {
        if((row > isl->getRows()-1) && isl->isOccupied(row-1, col) == false)
        {
            isl->moveCreature ( row, col, row-1, col );
            moved = true;
            break;
        }
    }

    }
}

//virtual breed
void Ant::breed()
{
    breedDaysPassed++;
    if(breedDaysPassed >= 3)
    {
        if((col>0) && isl->isOccupied(row, col-1) == false)
        {
            Ant *createNewAnt = new Ant(isl, row, col-1);
            isl->addCreature(createNewAnt, row, col-1);
            breedDaysPassed = 0;
        }
        else if((col < isl->getCols()-1) && isl->isOccupied(row, col+1) == false)
        {
            Ant *createNewAnt = new Ant(isl, row, col+1);
            isl->addCreature(createNewAnt, row, col+1);
            breedDaysPassed = 0;

        }
        else if((row > 0) && isl->isOccupied(row-1, col) == false)
        {
            Ant *createNewAnt = new Ant(isl, row-1, col);
            isl->addCreature(createNewAnt, row-1, col);
            breedDaysPassed = 0;

        }
        else if((row < isl->getRows()-1) && (isl->isOccupied(row+1, col) == false))
        {
            Ant *createNewAnt = new Ant(isl, row+1, col);
            isl->addCreature(createNewAnt, row+1, col);
            breedDaysPassed = 0;

        }
    }
}
