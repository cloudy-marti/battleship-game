#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"



int main(){

	_world = (World*)malloc(sizeof(World));
	printf("move with WASD and press enter ...\n\n if you want to attack, press spacebar and enter");
	
	printf("Votre choix : %s\n", directionInput());

	displayBoard(world);
}