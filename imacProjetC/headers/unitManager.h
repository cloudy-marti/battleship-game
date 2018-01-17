#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

Unit* initializeUnit(char player, char type);
int placeUnitInput(char axis, int size);
void emptyBuffer();
void placeUnit(Unit* unit);
void placeAllUnit();