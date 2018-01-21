#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/structures.h"
#include "headers/board.h"
#include "headers/playerManagerV2.h"
#include "headers/turnManager.h"
#include "headers/turnManager.h"

void initializeGame(){
	// Préparation du terrain : création et initialization du board
	// Énonciation des règles
	// Préparation des pions

	_world = (World*)malloc(sizeof(World));

	displayBoard(_world);
	placeAllUnit();
}

void manageTurn(){

	char* directionInput = initializeDirectionInput();


	void iterateList(_world->blueList, directionInput);
	void iterateList(_world->redList, directionInput);
	
	freeDirectionInput(directionInput);
}

int iterateUnitList(unitList list, char* directionInput){ // = (Unit* list)

	int unitTurn;
	// parcourir une liste chaînée
	for(unitTurn = 0; list != NULL; list = list->next, unitTurn++){
		unitMove(list, directionInput);
	}
	// if(list == NULL), on ne rentre pas dans la boucle et la fonction fait un return direct
	return unitTurn;
}

void turnPlayer(unitList list, char* directionInput, char* playerEnemyName){

	unitTurn = iterateUnitList(list, directionInput);
	if(unitTurn == 0){
		printf("%s won the game !\n", playerEnemyName);
		quitGame(directionInput, list);
	}
}