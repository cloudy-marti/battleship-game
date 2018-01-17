#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

void displayBoard(p_World world);

void displayBoard(p_World world){ // world->board[1][1] j'accède à la première case du board

	int i, j;

	for(j = 0; j < HEIGHT; j++){
		for(i = 0; i < WIDTH; i++){
			printf("-----");
		}
		printf("-\n");

		for(i = 0; i < WIDTH; i++){
			if(world->board[i][j] == NULL){
				printf("|    ");
			}else{
				printf("| %c%c ", world->board[i][j]->player, world->board[i][j]->type);
			}
		}
		printf("|\n");
	} // tableau parcouru de haut en bas -> à chaque boucle, on a parcouru une colonne

	for(i = 0; i < WIDTH; i++){
		printf("-----");
	}
	printf("-\n");
}

int main(){

	p_World world = (World*)malloc(sizeof(World));

	displayBoard(world);
}
