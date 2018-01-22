#include <stdio.h>
#include <stdlib.h>
#include "headers/typedefs.h"
#include "headers/board.h"

void displayBoard(){ // world->board[1][1] j'accède à la case (1,1) du board

	int i, j;

	for(j = 0; j < HEIGHT; j++){
		for(i = 0; i < WIDTH; i++){
			printf("-----");
		} // cette boucle permet de créer la ligne -------- qui va délimiter les parties horizontales des cases
		printf("-\n"); 

		for(i = 0; i < WIDTH; i++){
			if(_world->board[i][j] == NULL || _world->board[i][j]->isAlive == 0){
				printf("|    ");
			}else{
				printf("| %c%c ", _world->board[i][j]->player, _world->board[i][j]->type);
			}
		}
		// cette boucle va afficher le contenu de la case, vide ou contenant un pion
		// _world->board[i][j] == NULL, cela veut dire que cette case ne pointera sur aucune unité, donc la case s'affichera vide
		// _world->board[i][j]->isAlive == 0, on considère que le pion a été tué, donc la case s'affiche vide
		printf("|\n");
	} // tableau parcouru de haut en bas -> à chaque boucle, on a parcouru une colonne

	for(i = 0; i < WIDTH; i++){
		printf("-----");
	}
	printf("-\n");
}

void gameInstructions(){
	printf("kill your enemies\nchoose your direction with WASD\nPress q to quit\n");
}