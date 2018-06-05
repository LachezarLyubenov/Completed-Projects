#ifndef DOODLEBUG_H
#define DOODLEBUG_H

#include <iostream>

#include "Creature.h"

class Doodlebug : public Creature
{
public:
    Doodlebug(Island *island, int row, int col);
    ~Doodlebug(){};
    void breed() override;
    void hunt() override;
    void move() override;
    bool starved();
        
private:
    
    int starveCounter;
};

#endif