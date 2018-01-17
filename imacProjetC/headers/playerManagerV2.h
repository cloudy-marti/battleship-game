#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

char* directionInput();
int checkInput(char* input);
void unitMove(Unit* unit);
void unitAttack(Unit* unit);
void deadUnit(Unit* unit);