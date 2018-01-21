#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/structures.h"
#include "headers/board.h"
#include "headers/playerManagerV2.h"
#include "headers/turnManager.h"
#include "headers/turnManager.h"

Unit* initializeUnit(char player, char type){
	Unit* unit = (Unit*)malloc(sizeof(Unit));
	// il y a toujours une étoile de plus dans le cast que dans le paramètre de sizeof
	// exemple : (Unit**)malloc(sizeof(Unit*))

	if(unit == NULL){
		exit(EXIT_FAILURE);
	}

	unit->player = player;
	unit->type = type;
	// Assignation / affectation de valeur
	// convention imposée : la case mémoire qui va recevoir la valeur est à gauche
	// la valeur qui va être rangée dans la case mémoire est à droite
	unit->next = NULL;

	return unit;
}

int placeUnitInput(char axis, int size){ // playerManager svp
	int newPosition;

	printf("choose your %c position between 0 and %d\n", axis, size-1);
	scanf("%d", &newPosition);
	emptyBuffer();

	while(newPosition < 0 || newPosition >= size){
		printf("try again\n");
		scanf("%d", &newPosition);
		emptyBuffer();
	}

	return newPosition;
}

void emptyBuffer(){ // playerManager
  int unitBuffer;
  while((unitBuffer=getchar()) != EOF && unitBuffer != '\n');
  // fonction qui va nous permettre de vider le buffer qui va être rempli par un joueur pas doué
  // qui va écrire n'importe quoi (pas des int) dans les fonctions ci-dessus

  // EOF est un caractère qui désigne la fin d'un fichier
  // !! demander ce que c'était exactement le buffer 
}

void placeUnit(Unit* unit){
	// fonction qui va permettre au joueur de placer ses unités dans board
	// au début du jeu
	unit->posX = placeUnitInput('X', WIDTH);
	unit->posY = placeUnitInput('Y', HEIGHT);
	
	_world->board[unit->posX][unit->posY] = unit;
}

void placeAllUnit(){

	_world->blueList = playerPlaceUnits(BLUE, "blue");
	_world->redList = playerPlaceUnits(RED, "red");
}

Unit* playerPlaceUnits(char player, char* playerName){

	int i;

	char unitType[3] = {SERF, SERF, WARRIOR};
	char* unitTypeName[3] = {"serf", "serf", "warrior"};

	unitList list = NULL;
	// premier maillon de ma list, même si elle est nulle

	printf("the %s team must place their unit\n", playerName);
	for(i = 0; i < 3; i++){
		Unit* newUnit = chooseUnit(player, unitType[i], unitTypeName[i]);
		list = addUnit(list, newUnit);
	}

	return list;
}

Unit* chooseUnit(char player, char type, char* typeName){

	Unit* unit = initializeUnit(player, type);
	printf("Place your %s ..\n", typeName);
	placeUnit(unit);

	return unit;
}

Unit* addUnit(Unit* unit, Unit* newUnit){

	if(unit == NULL){
		return newUnit;
		// si unit n'existe pas, newUnit est considéré le début de la liste
		// ce même si newUnit == NULL, parce que l'utilisateur de la fonction addUnit est censé
		// donner une newUnit non nulle
	}

	unit->next = newUnit;
	return unit;
	// je retourne le premier élément de la liste
}