#include <stdio.h>
#include <stdlib.h>
#include "headers/structures.h"
#include "headers/board.h"
#include "headers/playerManagerV2.h"
#include "headers/unitManager.h"
#include "headers/turnManager.h"

void displayBoard(p_World world);
void gameInstructions();

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

void gameInstructions(){
	printf("kill your enemies\nchoose your direction with WASD\nPress q to quit\n");
}

int main(){

	_world = (World*)malloc(sizeof(World));

	displayBoard(_world);
	gameInstructions();
}
