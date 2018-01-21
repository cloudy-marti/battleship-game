#ifndef PLAYERMANAGERV2__H
#define PLAYERMANAGERV2__H

int placeUnitInput(char axis, int size);
void emptyBuffer();
char* initializeDirectionInput();
char* directionInput(char* playerInput);
int checkInput(char* input);

#endif