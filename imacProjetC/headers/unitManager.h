#ifndef UNITMANAGER__H
#define UNITMANAGER__H

#include "typedefs.h"

Unit* initializeUnit(char player, char type);
void placeUnit(Unit* unit);
void placeAllUnit();
Unit* playerPlaceUnits(char player, char* playerName);
Unit* chooseUnit(char player, char type, char* typeName);
Unit* addUnit(Unit* unit, Unit* newUnit);
void unitMove(Unit* unit, char* direction);
void deadUnit(Unit* unit);
void quitGame(char* directionInput);
void freeAll();
void freeList(unitList list);

#endif