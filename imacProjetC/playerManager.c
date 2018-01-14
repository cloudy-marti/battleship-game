#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

char* getInput(){

    const int taille = 3;    
	char* player = (char*)malloc(sizeof(char)*taille); // = malloc(3)

	// on lui dit à malloc de nous donner autand de mémoire qu'ont besoin 3 char (donc, 1 octet * 3)
	// sizeof est lui-même une fonction, voire plutôt un utilitaire, presque une fonction, qui va retourner une valeur qu'il aura calculé à partir des paramètres entrés
	// malloc va renvoyer un void pointeur. Du coup, il va falloir faire un "cast" pour changer le void au type recherché (forcément un pointeur)

    printf("move with WASD and press enter\n");
    
    while(checkInput(player) == -1){
        scanf("%s", player);
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

	if (input[0] == input[1]) {
		return -1
	}
	
    return 0; // si ya pas de cas d'erreurs, je retourne 0
}

void unitMove(Unit unit){

	int i;
	int translationX = 0;
	int translationY = 0;

	char* player = getInput();

	for(i = 0; player[i] != '\0'; i++){
		switch(player[i]){
			case('w') :
				--translationY;
				break;
			case('s') :
				++translationY;
				break;
			case('a'):
				--translationX;
				break;
			case('d'):
				++translationX;
			default :
				break;
		}
	}


	// Condition ternaire : (condition) ? code a executer si vrai, genre "si" : code a executer si faux, genre "else"
	// on peut enlever le break du case D parce que dans default il n'y a pas d'instructions.
	// le switch est comme une combinaison de for et de if. Le break sert à sortir du switch lorsque la condition a été faite


}

int main(){

	pWorld world = (World*)malloc(sizeof(World));
	printf("Tapez votre choix\n");
	printf("Votre choix : %s\n", getInput());

	displayBoard(world);
}