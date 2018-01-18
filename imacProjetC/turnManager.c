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

void onPlayerTurnUnitTurn(){
	// pendant que le joueur joue, dire à quelle unité c'est le tour
	// quoique c'est geré dans unitMove je crois
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

//?¿ ou c'est exit game dans game.c ?

char endGameInput(){

	char endGameInput = '\0';

	scanf("%c", &endGameInput);
    return endGameInput;
}

void endGame(){

	char endGame = endGameInput();

	if(endGame == 'q'/* || toutes les unités d'une équipe pointent vers NULL car elles ont été toutes tuées*/){
		exit(-1); // shit ça sert à rien TT
	} else return;
}