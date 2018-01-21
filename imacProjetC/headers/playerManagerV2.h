#ifndef PLAYERMANAGERV2__H
#define PLAYERMANAGERV2__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

char* directionInput();
int checkInput(char* input);
void unitMove(Unit* unit, char* direction);
void unitAttack(Unit* unit);
void deadUnit(Unit* unit);
void quitGame();

#endif