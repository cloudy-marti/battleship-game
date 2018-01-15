#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

// on playerManager :
// unitMove
// unitAttack
// deadUnit

// schéma game /turnManager/playerManager/etc ...
// est-ce que les fichiers qui composent le game peuvent appeler des fonctions entre eux ?
// tant que game est appelé nulle part ?

int placeUnitInputX(){
	// scanf des valeurs choisies par le joueur
	int posX;

	printf("choose your X position between 0 and 11\n");
	scanf("%d", posX);

	if(posX < 0 || posX > 11){
		printf("try again\n");
		scanf("%d", posX);
	} else return posX;

}

int placeUnitInputY(){

	int posY;

	printf("choose your Y position between 0 and 17\n");
	scanf("%d", posY);

	if(posY < 0 || posY > 17){
		printf("try again\n");
		scanf("%d", posY);
	} else return posY;

}

void placeUnit(Unit* unit){
	// fonction qui va permettre au joueur de placer ses unités dans board
	// au début du jeu ou à la demande de la reine (amélioration)

	unit = _world->board[placeUnitInputX()][placeUnitInputY()];
}