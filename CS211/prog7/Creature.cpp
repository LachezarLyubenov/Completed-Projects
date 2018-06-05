#include <cstdlib>
#include <ctime>


#include "Creature.h"
#include "Doodlebug.h"
#include "Ant.h"

Creature::Creature(Island *island, int row, int col)
   {
    isl = island;
    this->row = row;
    this->col = col;
    moved = false;
    breedDaysPassed = 0;
    //bugType = type;
   }

Creature::~Creature(){}


void Creature::move()
{

}

void Island::resetCreatures()
{
  for (int i = 0; i < rows; i++)
  {
    for(int j = 0; j < cols; j++)
    {
      if(location[i][j] != NULL)
      {
        location[i][j]->moved = false;
      }
    }
  }
}

void Island::moveCreatures() 
{
  for (int i = 0; i < rows; i++)
  {
    for(int j = 0; j < cols; j++)
    {
      if(location[i][j] != NULL)
      {
        if(location[i][j]->getBugType() == 'D' && !location[i][j]->moved)
        {
          location[i][j]->moved = true;
          location[i][j]->move();
        }
      }
    }
  }

  for (int i = 0; i < rows; i++)
  {
    for(int j = 0; j < cols; j++)
    {
      if(location[i][j] != NULL)
      {
        if(location[i][j]->getBugType() == 'a' && !location[i][j]->moved)
        {
          location[i][j]->moved = true;
          location[i][j]->move();
        }
      }
    }
  }
}

void Island::checkForDeath()
{
  for (int i = 0; i < rows; i++)
  {
    for(int j = 0; j < cols; j++)
    {
      if(location[i][j] != NULL && location[i][j]->getBugType() == 'D')
      {
        Doodlebug *newDoodle = (Doodlebug*) location[i][j];
        if(newDoodle->starved())
        {
          deleteBug(i, j);
        }
      }
    }
  }
}

void Island::feedTheBuggers()
{
  for (int i = 0; i < rows; i++)
  {
    for(int j = 0; j < cols; j++)
    {
      if(location[i][j] != NULL && location[i][j]->getBugType() == 'D' && location[i][j]->moved == false)
      {
        location[i][j]->hunt();
      }
    }
  }
}


void Island::checkForBreeding()
{
  for (int i = 0; i < rows; i++)
  {
    for(int j = 0; j < cols; j++)
    {
      if(location[i][j] != NULL)// && location[i][j]->moved == true)
      {
        location[i][j]->breed();
      }
    }
  }
}


void Island::dailyRoutine()
{
  resetCreatures();
  feedTheBuggers();
  checkForBreeding();
  checkForDeath();
  moveCreatures();
}

void Creature::breed()
{

}
void Creature::hunt()
{

}

char Creature::setBugType(char type)
{
  bugType = type;
}

Island::Island(GridDisplay *grid)
{

  gd = grid;
  rows = 20;
  cols = 20;
  location = new Creature**[rows];

  for( int i = 0; i < rows; i++)
  {
    location[i] = new Creature*[cols];
    for (int k = 0; k < cols; k++)
    {
      location[i][k] = NULL;
    }
  }

  int dailyAnt = 100;
  int dailyDoodle = 5;
  int antCounter = 0;
  int doodleCounter = 0;
  srand(time(NULL));

  while(antCounter < dailyAnt)
  {
    int row = rand() % getRows();
    int col = rand() % getCols();
    if(location[row][col] == NULL)
    {
      Ant *ants = new Ant(this, row, col);
      addCreature(ants, row, col);
      location[row][col]->setBugType('a');
      grid->setChar(row, col , 'a');
      antCounter++;
    }
  }


  while(doodleCounter < dailyDoodle)
  {
    int row = rand() % getRows();
    int col = rand() % getCols();
    if(location[row][col] == NULL)
    {
      Doodlebug *newDoodle = new Doodlebug(this, row, col);
      addCreature(newDoodle, row, col);
      location[row][col]->setBugType('D');
      grid->setChar(row, col , 'D');
      doodleCounter++;
    }
  }

}

int Island::getRows()
{
    return rows;
}

int Island::getCols()
{
    return cols;
}
 
bool Island::isValid (int r, int c)
{
    if (( r >= 0 && r < rows ) && ( c >= 0 && c < cols))
      return true;
    else
      return false;
}
   
bool Island::isOccupied (int r, int c)
{
    if ( location[r][c] == NULL )
      return false;
    else
      return true;
}

bool Island::addCreature (Creature* b, int r, int c)
{
    // verify to location is valid
    if ( isValid (r, c) == false )
      return false;
    // verify to location is empty
    if ( isOccupied (r, c) == true)
      return false;
    location[r][c] = b;
    if(location[r][c]->getBugType() == 'a')
    {
      gd->setChar(r, c, 'a'); 
    }
    else if (location[r][c]->getBugType() == 'D')
    {
      gd->setChar(r, c, 'D'); 
    }
    return true;
}

bool Island::moveCreature (int oldX, int oldY, int nextX, int nextY)
{
    if ( isValid (oldX, oldX) == false )
      return false;
    if ( isValid (nextX, nextY) == false )
      return false;
    if ( isOccupied (oldX, oldX) == false)
      return false;
    if ( isOccupied (nextX, nextY) == true)
      return false;
    if(location[nextX][nextY] == NULL)
    {
      return false;
    }
    location[nextX][nextY] = location[oldX][oldY];
    //delete location[oldX][oldY];
    gd->setChar (oldX, oldY, '.');
    location[oldX][oldY] = NULL; 

    if(getBug(nextX, nextY)->getBugType() == 'a')
    {
      gd->setChar(nextX, nextY, 'a'); 
    }
    else if (getBug(nextX, nextY)->getBugType() == 'D')
    {
      gd->setChar(nextX, nextY, 'D'); 
    }
    //gd->setChar(nextX, nextY, location[nextX][nextY]->getBugType()); 
    return true;
}

Creature *Island::getBug(int r, int c)
{
  return location[r][c];
}


void Island::deleteBug(int r, int c)
{
  if(isValid(r, c) && isOccupied(r, c))
  {
    delete location[r][c];
    gd->setChar (r, c, '.');
    location[r][c] = NULL; 

  }
}

char Creature::getBugType()
{
  return bugType;
}