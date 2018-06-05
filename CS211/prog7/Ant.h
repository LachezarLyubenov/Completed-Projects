#ifndef ANT_H
#define ANT_H

#include "Creature.h"

class Ant: public Creature
{
    //friend class Island;
public:
    Ant(Island *island, GridDisplay *grid);
    Ant(Island *island, int row, int col);
    ~Ant(){};
    void breed() override;
    void move() override;

};

#endif