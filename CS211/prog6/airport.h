#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "myList.h"

class Airport
{
private:
// Create the Data Members for the Airport class here
MyList* airportList;
bool visited;
int howMany;

public:
Airport();
~Airport();

void addNew(int m);
bool wasVisited();

};
