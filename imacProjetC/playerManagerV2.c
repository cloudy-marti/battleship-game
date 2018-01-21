#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/structures.h"
#include "headers/board.h"
#include "headers/playerManagerV2.h"
#include "headers/turnManager.h"
#include "headers/turnManager.h"

char* initializeDirectionInput(){

	const int taille = 3;
	return (char*)malloc(sizeof(char)*taille); // = malloc(3)
	// malloc sert à initialiser un pointeur

	// on lui dit à malloc de nous donner autand de mémoire qu'ont besoin 3 char (donc, 1 octet * 3)
	// sizeof est lui-même une fonction, voire plutôt un utilitaire, presque une fonction, qui va retourner une valeur qu'il aura calculé à partir des paramètres entrés
	// malloc va renvoyer un void pointeur. Du coup, il va falloir faire un "cast" pour changer le void au type recherché (forcément un pointeur)
	// dans ce cas le cast est le (*char) qu'on a rajouté devant malloc
	// parce qu'on fait une égalité entre char* player et le malloc qui doit être donc un char* aussi
}

char* directionInput(char* playerInput){

	playerInput = "  \0"; // = {' ', ' ', '\0'};

    while(checkInput(playerInput) == -1){
    	printf("try again\n");
        scanf("%s", playerInput);
        playerInput[2] = '\0';
    }

//    free(playerInput); // il ne faudrait pas plutot le mettre dans la fonction qui va l'appeler ?

    return playerInput;
}

int checkInput(char* input){

    int i;

    for(i = 0; input[i] != '\0'; i++){
        if(input[i] == 'q'){
        	quitGame(input);
        }else if(!(input[i] == 'w'
            || input[i] == 'a' 
            || input[i] == 's' 
            || input[i] == 'd')){
            return -1;
            // input[i] = 'qqe chose' sont mes conditions sans erreurs, si je les met entre !() j'inverse la condition, donc je pourrait envoyer mon code d'erreur -1 à partir de là
        }
    }

    if(strcmp(input, "ws") == 0 // ça c'est égal à : !strcmp(*input, "ws")
        || strcmp(input, "sw") == 0
        || strcmp(input, "ad") == 0 
        || strcmp(input, "da") == 0){
        return -1;
    }

    // à la base c'était strcmp(*input, "da"), j'ai enlevé l'étoile
    // parce que la fonction c'est "int strcmp(const char* s1, const char* s2)"
    // et input est déjà de type char*

	if (input[0] == input[1]) {
		return -1;
	}
	
    return 0; // si ya pas de cas d'erreurs, je retourne 0
}

void unitMove(Unit* unit, char* direction){ // unitManager

	int i;
	int translationX = 0;
	int translationY = 0;

	char* player = directionInput(direction);

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

	// Unit* tmpUnit = _world->board[posX+translationX][posY+translationY];
	// le compilateur n'est pas content
	Unit* tmpUnit = _world->board[unit->posX+translationX][unit->posY+translationY];
	// posX ou posY seuls ne sont pas déclarés ailleurs, donc j'ai changé par unit->posX/Y
	// car unit est mon pointeur sur mon Unit originale à la position posX/Y initiales

	// j'ai récupéré la case du tableau où le joueur veut aller
	// je la teste ci-dessous, car le joueur va pouvoir se déplacer ssi la case est vide

	// dans le cas où tmpUnit != NULL ->
	// unit passée en paramètre est l'unité qui va attaquer, et tmpUnit est l'unitée qui va prendre

	if(tmpUnit == NULL){

		tmpUnit = unit;
		unit = NULL;
		// Alors, tmpUnit va prendre l'adresse pour Unit (dont la mémoire est allouée), ce qui va simuler le fait que Unit va se déplacer dans cette case du tableau
		// unit va donc être NULL, sinon deux cases pointeraient sur le même Unit
		// Le compilateur n'aurait rien dit, mais il y aurait une erreur de comportement : ce n'est pas ce qui est demandé
		// erreur de comportement : lorsque le joueur demanderais à ce déplacer, la même Unit se "doublerait" dans la case demandée

		// en fait le tableau est constitué d'adresses sur unité
		// Lorsqu'il n'y a pas d'unité, la case pointe sur NULL

		// une autre façon de faire :

		// Unit* swapUnit = tmpUnit; // je sauvegarde la valeur de tmpUnit dans swapUnit
		// tmpUnit = unit; // j'attribue à tmpUnit la valeur de unit
		// unit = swapUnit;

		// // SER : Sauvegarder - Ecraser - Restaurer
		// // pour faire un swap il faut penser à ça
		// // c'est cool mais ça a pu s'améliorer
		// // tout simplement parce qu'on avait pas besoin de sauvegarder la valeur de unit 
	}
	// on a enregistré la position du personnage et l'endroit où il veut attaquer	
	else if(unit->player == tmpUnit->player){
		return;
	}
	// Ici on dit que si l'unité attaquée est de la même couleur (donc même équipe), on sort de la fonction attackUnit
	else if(unit->type == WARRIOR || tmpUnit->type == SERF){
		deadUnit(tmpUnit);
	}
	else deadUnit(unit);
	// si je suis warrior OU mon enemi est un serf, l'enemi va mourrir
	// dans l'autre cas (serf vs warrior), je part de la fonction unitAttack
	// car le joueur a tenté d'attaquer une unité plus forte, donc a échoué

	return;
}

void deadUnit(Unit* unit){ // unitManager

	// free(unit);
	unit->isAlive = 0;
	// unit = NULL;
	// On va appeler deadUnit(Unit* unit) lorsque la condition de succès d'attaque c'est confirmée
	// Unit* unit passé en paramètre va être l'unité attaquée
	// du coup on va convertir cette unité en pointeur sur NULL pour dire qu'elle pointera plus sur une unité
	// donc la case du tableau va afficher du vide
	// car dans board.c un pointeur sur NULL de type Unit affiche la case vide (lignes 16-21)
}

void quitGame(char* directionInput){
	printf("you quit the game!\n");
	free(directionInput);
	directionInput = NULL;

	freeList(_world->redList);
	freeList(_world->blueList);

	exit(0);
}

void freeList(unitList list){

	unitList tmpList;

	for(tmpList = NULL; list != NULL; ){
		tmpList = list;
		list = list->next;
		free(tmpList);
	}
	// on a fait malloc pour allouer de la mémoire pour les unités
	// de la liste quelque part, du coup on libère la mémoire

}