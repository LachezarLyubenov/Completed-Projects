#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "myList.h"
#include "airport.h"
#include "myListNode.h"


class TravelNetwork
{
private:
// Create the Data Members for the Travel Network here
Airport* network;
int numberOfAirplanes;

public:
TravelNetwork();
~TravelNetwork();
void processCommandLoop (FILE* inFile);
void showCommands();
void doTravel();
void doResize();
void doInsert();
void doDelete();
void doList();
void doFile();

void depthFirstSearchHelper(int x, int y);
bool depthFirstSearch(int x, int y);

};
