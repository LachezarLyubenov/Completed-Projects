#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "airport.h"


Airport::Airport()
{
        this->howMany = 5;
        this->airportList = new MyList [ this->howMany ];
}
Airport::~Airport()
{
        Airport::~Airport();
}

void Airport::addNew(int m)
{

}

bool Airport::wasVisited()
{
        return 1;
}
