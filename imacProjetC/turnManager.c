#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

/*
void displayBoard(p_World world);

char* directionInput();
int checkInput(char* input);
void unitMove(Unit* unit);
void unitAttack(Unit* unit);
void deadUnit(Unit* unit);

Unit* initializeUnit(char player, char type);
int placeUnitInput(char axis, int size);
void emptyBuffer();
void placeUnit(Unit* unit);
void placeAllUnit();
*/

void beginGame(){
	// le moment de dire qu'il faut placer les unités
}

/*char* onPlayerTurnUnitTurnInput(){
	// le joueur peut choisir l'unité qu'il va bouger ensuite
	// amélioration
}*/

void onPlayerTurnUnitTurn(){
	// pendant que le joueur joue, dire à quelle unité c'est le tour
	
}

void nextPlayer(){
	// utiliser world->turn
	// j'avoue que je ne comprend pas la struct world (comment l'utiliser)
	// lorsque unit* board[ ][ ] a changé (unitMove/unitAttack), turn++ ?
	// donc on fait une boucle ? :/
	// comment on dit qu'une fonction a été réalisée ? (avec ou sans code d'erreur)
	// lorsque la boucle a été terminée (3 pour trois unités par equipe), on change de unitList
	// unitList est un pointeur sur Unit
	// ^ ma logique...
}

char endGameInput(){

	char endGameInput = '\0';

	scanf("%c", &endGameInput);
    return endGameInput;
}

void endGame(){

	char endGame = endGameInput();

	if(endGame == 'q'/* || toutes les unités d'une équipe pointent vers NULL car elles ont été toutes tuées*/){
		exit(-1); // ça sert à rien TT
	} else return;
}