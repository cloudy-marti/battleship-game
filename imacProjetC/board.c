#include <stdio.h>
#include <stdlib.h>
#include "headers/typedefs.h"
#include "headers/board.h"

void displayBoard(){ // world->board[1][1] j'accède à la première case du board

	int i, j;

	for(j = 0; j < HEIGHT; j++){
		for(i = 0; i < WIDTH; i++){
			printf("-----");
		}
		printf("-\n");

		for(i = 0; i < WIDTH; i++){
			if(_world->board[i][j] == NULL || _world->board[i][j]->isAlive == 0){
				printf("|    ");
			}else{
				printf("| %c%c ", _world->board[i][j]->player, _world->board[i][j]->type);
			}
		}
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