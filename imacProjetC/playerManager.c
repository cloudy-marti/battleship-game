#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

char* getInput(){

    int i;
    const int taille = 3;    
    char player[taille] = {'0', '0', '\0'};

    printf("move with WASD and press enter\n");
    
    while(checkInput(player) == -1){
        scanf("%s", &player);
        player[2] = '\0';
    }

    return player;
}

int checkInput(char* input){

    int i;

    for(i = 0; input[i] != '\0'; i++){
        if(!(input[i] = 'w' 
            || input[i] = 'a' 
            || input[i] = 's' 
            || input[i] = 'd')){
            return -1; // input[i] = qqe chose sont mes conditions sans erreurs, si je les met entre !() j'inverse la condition, donc je pourrait envoyer mon code d'erreur -1 à partir de là
        }
    }

    if(strcmp(*input, "ws") == 0 // ça c'est égal à : !strcmp(*input, "ws")
        || strcmp(*input, "sw") == 0
        || strcmp(*input, "ad") == 0 
        || strcmp(*input, "da") == 0){
        return -1
    }

    // ww cas d'erreur -> le faire

    return 0; // si ya pas de cas d'erreurs, je retourne 0
}

void unitMove(Unit unit){

	int i;
	int translationX = 0;
	int translationY = 0;

	char* player = getInput();

	for(i = 0; player[i] != '\0'; i++){
		switch(player){
			case("w") :
				unit->posY--;
				break;
			case("s") :
				unit->posY++;
				break;
			case("a"):
				unit->posX--;
				break;
			case("d"):
				unit->posX++;
			default :
				break;
		}
	}

	// on peut enlever le break du case D parce que dans default il n'y a pas d'instructions.
	// le switch est comme une combinaison de for et de if. Le break sert à sortir du switch lorsque la condition a été faite 
}

int main(){

	pWorld world = (World*)malloc(sizeof(World));

	displayBoard(world);
}
