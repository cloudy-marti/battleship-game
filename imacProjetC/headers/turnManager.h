#ifndef TURNMANAGER__H
#define TURNMANAGER__H
#include "typedefs.h"

void initializeGame();
void manageTurn();
int iterateUnitList(unitList list, char* directionInput);
void turnPlayer(unitList list, char* directionInput, char* playerEnemyName);

#endif