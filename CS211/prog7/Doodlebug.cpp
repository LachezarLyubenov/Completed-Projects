//Doodlebug class
#include "Doodlebug.h"


//constructor for Doodlebug
Doodlebug::Doodlebug(Island *island, int row, int col) : Creature(island, row, col)
{
    starveCounter = 0;
    bugType = 'D';
}

//virtual move function
void Doodlebug::move()
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
        if((col> isl->getCols()-1) && isl->isOccupied(row, col+1) == false)
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
        if((row> isl->getRows()-1) && isl->isOccupied(row-1, col) == false)
        {

            isl->moveCreature ( row, col, row-1, col );
            moved = true;
            break;
        }
    }

    }
}

//virtual hunt function
void Doodlebug::hunt()
{
    starveCounter++;
    if(col > 0) 
    {
        if (isl->isOccupied(row, col-1) == true && isl->getBug(row, col-1)->getBugType() == 'a')
        {
            isl->deleteBug(row, col-1);
            isl->moveCreature(row, col, row, col-1);
            moved = true;
            starveCounter = 0;
        }
    }
    else if(col < isl->getCols()-1)
    {
        if(isl->isOccupied(row, col+1) == true && isl->getBug(row, col+1)->getBugType() == 'a')
        {
            isl->deleteBug(row, col+1);
            isl->moveCreature(row, col, row, col+1);
            moved = true;
            starveCounter = 0;
        }
    }
    else if((row > 0))
    {
        if(isl->isOccupied(row-1, col) == true && isl->getBug(row-1, col)->getBugType() == 'a')
        {
            isl->deleteBug(row-1, col);
            isl->moveCreature(row, col, row-1, col);
            moved = true;
            starveCounter = 0;
        }
    }
    else if((row < isl->getRows()-1))
    { 
        if(isl->isOccupied(row+1, col) == true && isl->getBug(row+1, col)->getBugType() == 'a')
        {
            isl->deleteBug(row+1, col);
            isl->moveCreature(row, col, row+1, col);
            moved = true;
            starveCounter = 0;
        }
    }
}

//virtual breed 
void Doodlebug::breed()
{
    breedDaysPassed++;
    if(breedDaysPassed >= 8)
    {
        if((col>0) && isl->isOccupied(row, col-1) == false)
        {
            Doodlebug *newDoodle = new Doodlebug(isl, row, col-1);
            isl->addCreature(newDoodle, row, col-1);
            this->breedDaysPassed = 0;
        }
        else if((col < isl->getCols()-1) && isl->isOccupied(row, col+1) == false)
        {
            Doodlebug *newDoodle = new Doodlebug(isl, row, col+1);
            isl->addCreature(newDoodle, row, col+1);
            this->breedDaysPassed = 0;
        }
        else if((row > 0) && isl->isOccupied(row-1, col) == false)
        {
            Doodlebug *newDoodle = new Doodlebug(isl, row-1, col);
            isl->addCreature(newDoodle, row-1, col);
            this->breedDaysPassed = 0;

        }
        else if((row < isl->getRows()-1) && (isl->isOccupied(row+1, col) == false))
        {
            Doodlebug *newDoodle = new Doodlebug(isl, row+1, col);
            isl->addCreature(newDoodle, row+1, col);
            this->breedDaysPassed = 0;
        }
    }
} 
    
bool Doodlebug::starved()
{
    if(this->starveCounter >= 3)
    {
        return true;
    }
    else{
        return false;
    }
}
