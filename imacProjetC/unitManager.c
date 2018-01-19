#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/structures.h"

Unit* initializeUnit(char player, char type);
int placeUnitInput(char axis, int size);
void emptyBuffer();
void placeUnit(Unit* unit);
void placeAllUnit();

// on playerManager :
// unitMove
// unitAttack
// deadUnit

// schéma game /turnManager/playerManager/etc ...
// est-ce que les fichiers qui composent le game peuvent appeler des fonctions entre eux ?
// tant que game est appelé nulle part ?

/*int placeUnitInputX(){
	// scanf des valeurs choisies par le joueur pour placer ses unités au début
	int posX;

	printf("choose your X position between 0 and 11\n");
	scanf("%d", posX);

	if(posX < 0 || posX > 11){
		printf("try again\n");
		scanf("%d", posX);
		emptyBuffer();
	} else return posX;
}

int placeUnitInputY(){

	int posY;

	printf("choose your Y position between 0 and 17\n");
	scanf("%d", posY);

	if(posY < 0 || posY > 17){
		printf("try again\n");
		scanf("%d", posY);
		emptyBuffer();
	} else return posY;
}*/

Unit* initializeUnit(char player, char type){
	Unit* unit = (Unit*)malloc(sizeof(Unit));
	// il y a toujours une étoile de plus dans le cast que dans le paramètre de sizeof
	// exemple : (Unit**)malloc(sizeof(Unit*))
	unitList* list = (unitList*)malloc(sizeof(unitList)); // ¿?¿?¿?

	if(list == NULL || unit == NULL){
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
	// au début du jeu ou à la demande de la reine (amélioration)
	unit = _world->board[placeUnitInput('X', WIDTH)][placeUnitInput('Y', HEIGHT)];
}

void placeAllUnit(){

	int i, j;

	// le compilateur me crache dessus si j'utilise int taille = 6;
	// pareil si je met const int taille
	// pour mettre unitType[taille] au lieu de unitType[6]
	// avec unitType[taille] il me dit que c'est un élément variable
	// avec un #define je pense que ça passerait
	
	char unitType[6] = {SERF, SERF, WARRIOR, SERF, SERF, WARRIOR};
	char* unitTypeName[6] = {"serf", "serf", "warrior", "serf", "serf", "warrior"};

	char unitPlayer[2] = {BLUE, RED};
	char* unitPlayerName[2] = {"blue", "red"};

	// pourquoi char puis char* ?
	// parce que le premier on va chercher directement le #define et le deuxième on désigne des chaînes de caractères ?

/*	printf("the BLUE team begin\n");
	for(i = 0; i < taille; i++){ // c'est pas plutôt taille / 2 ? 
		Unit* unit = initializeUnit(BLUE, unitType[i]);
		printf("Place your %s ..\n", unitTypeName[i]);
		placeUnit(unit);
		_world->blueList = unit;

		// faire une fonction pour factoriser le code en double
		// factoriser : faire une seule fonction pour les répétitions de fonctions
	}

	printf("the RED team after\n");
	for(i = 0; i < taille; i++){
		Unit* unit = initializeUnit(RED, unitType[i]);
		printf("Place your %s ..\n", unitTypeName[i]);
		placeUnit(unit);
		_world->redList = unit;
	}
	*/
}

void chooseUnit(char player, char type){

	Unit->player = player;
	Unit->type = type;

	for(i = 0; i < 2; i++){
		printf("the %s team", unitPlayerName[i]);

		for(j = 0; j < 6; j++){ // c'est pas plutôt taille / 2 ?

			Unit* unit = initializeUnit(unitPlayer[i], unitType[j]);
			printf("Place your %s ..\n", unitTypeName[j]);
			placeUnit(unit);
			_world->board = unit;// ...

		}
	}
}