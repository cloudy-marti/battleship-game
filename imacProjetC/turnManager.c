#include <stdio.h>
#include <stdlib.h>
#include "headers/turnManager.h"
#include "headers/playerManagerV2.h"
#include "headers/unitManager.h"
#include "headers/board.h"

void initializeGame(){
	// Préparation du terrain : création (le malloc) et initialization du board -> displayBoard
	// Énonciation des règles -> displayBoard
	// Préparation des pions -> placeAllUnit : initialization, création de la liste des pions pour chaque joueur, placement des pions

	_world = (World*)malloc(sizeof(World));

	displayBoard(_world);
	placeAllUnit();
}

void manageTurn(){

	char* directionInput = initializeDirectionInput();

	while(1){ // while (1) le 1 veut dire quoi ?:o
		displayBoard();
		printf("Blue team turn!\n");
		turnPlayer(_world->blueList, directionInput, "red team");

		displayBoard();
		printf("Red team turn!\n");
		turnPlayer(_world->redList, directionInput, "blue team");
	}
}

int iterateUnitList(unitList list, char* directionInput){ // = (Unit* list)

	int unitTurn;
	int aliveUnit = 0;
	// parcourir une liste chaînée
	for(unitTurn = 0; list != NULL; list = list->next, unitTurn++){
		if(list->isAlive == 1){
			printf("Moving %s unit(%d:%d)", list->type == SERF ? "Serf" : "Warrior", list->posX, list->posY);
			unitMove(list, directionInput);
			++aliveUnit;
		}
	}
	// if(list == NULL), on ne rentre pas dans la boucle et la fonction fait un return direct
	return aliveUnit;
}

void turnPlayer(unitList list, char* directionInput, char* playerEnemyName){

	int unitTurn = iterateUnitList(list, directionInput);
	if(unitTurn == 0){
		printf("%s won the game !\n", playerEnemyName);
		quitGame(directionInput);
	}
}