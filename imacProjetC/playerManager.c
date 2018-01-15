#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

char* directionInput(){

    const int taille = 3;    
	char* player = (char*)malloc(sizeof(char)*taille); // = malloc(3)

	// malloc sert à initialiser un pointeur

	// on lui dit à malloc de nous donner autand de mémoire qu'ont besoin 3 char (donc, 1 octet * 3)
	// sizeof est lui-même une fonction, voire plutôt un utilitaire, presque une fonction, qui va retourner une valeur qu'il aura calculé à partir des paramètres entrés
	// malloc va renvoyer un void pointeur. Du coup, il va falloir faire un "cast" pour changer le void au type recherché (forcément un pointeur)
	// dans ce cas le cast est le (*char) qu'on a rajouté devant malloc
	// parce qu'on fait une égalité entre char* player et le malloc qui doit être donc un char* aussi

    while(checkInput(player) == -1){
    	printf("try again\n");
        scanf("%s", player);
        player[2] = '\0';
    }

    return player;
}

int attackInput(){

	const int taille = 2;
	char* player = (char*)malloc(sizeof(char)*taille);

	scanf("%s", player);
	player[1] = '\0';

	return -!(*player == " "); // true = 0 || false = -1

	// Déréférencer un pointeur veut dire aller là où le pointeur pointe, à l'occurence la valeur pointée
	
	// L'opérateur == va forcément retourner une valeur booléenne (0 ou 1).
	// Dans ma logique, 0 est le code de succès et -1 est le code d'erreur.
	// Or, ==  de base va retourner 0 lorsque l'égalité n'est pas vraie, et 1 lorsqu'elle est vraie.
	// Du coup, avec !( machin-truc ), on inverse la condition, car ! est un opérateur d'inversion, aussi appelée négation logique.
	// On ajoute - devant, pour avoir -1 au lieu de 1.
	// Donc, lorsque *player est un espace, on return 0.
	// Si *player n'est pas un espace, on return -1.

	free(*player); // je crois
}

int checkInput(char* input){

    int i;

    for(i = 0; input[i] != '\0'; i++){
        if(!(input[i] = 'w' 
            || input[i] = 'a' 
            || input[i] = 's' 
            || input[i] = 'd')){
            return -1;
            // input[i] = 'qqe chose' sont mes conditions sans erreurs, si je les met entre !() j'inverse la condition, donc je pourrait envoyer mon code d'erreur -1 à partir de là
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

void manageInputs(Unit* unit){
	
	if(attackInput() == 0){
		unitAttack(unit);
	}else{
		unitMove(unit);
	}
}

void unitMove(Unit* unit){

	int i;
	int translationX = 0;
	int translationY = 0;

	char* player = directionInput();

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

	Unit* tmpUnit = _world->board[posX+translationX][posY+translationY];

	// j'ai récupéré la case du tableau où le joueur veut aller
	// je la teste ci-dessous, car le joueur va pouvoir se déplacer ssi la case est vide

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

	return;
}

void unitAttack(Unit* unit){

	if(_world == NULL) return;
		// Comme il s'agit d'une fonction void, ce return va forcer la sortie de cette fonction
		// si _world est NULL pour une quelconque raison.
		// Ceci va éviter les SEGMENTATION FAULT
		// on a donc exclu le cas où on n'a pas de _world
		// c'est la première instruction de la fonction, parce que, en cas de manque de _world, ça évitera de créer toutes les variables et instructions du dessous
		// =optimisation wesh

	int i;

	int attackX = 0;
	int attackY = 0;

	int posX = unit->posX;
	int posY = unit->posY;

	char type = unit->type;

	char* player = directionInput();

	for(i = 0; player[i] != '\0'; i++){
		switch(player[i]){
			case('w') :
				--attackY;
				break;
			case('s') :
				++attackY;
				break;
			case('a'):
				--attackX;
				break;
			case('d'):
				++attackX;
			default :
				break;
		}
	}
	// on a enregistré la position du personnage et l'endroit où il veut attaquer

	Unit* enemyUnit = _world->board[posX+attackX][posY+attackY];
	// unit passée en paramètre est l'unité qui va attaquer, et enemyUnit est l'unitée qui va prendre
	char enemyType = enemyUnit->type;

	if(unit->player == enemyUnit->player) return;
	// Ici on dit que si l'unité attaquée est de la même couleur (donc même équipe), on sort de la fonction attackUnit

	if(type == 'w' || enemyType == 's') deadUnit(enemyUnit);
	else return;
	// si je suis warrior OU mon enemi est un serf, l'enemi va mourrir
	// dans l'autre cas (serf vs warrior), je part de la fonction unitAttack
	// car le joueur a tenté d'attaquer une unité plus forte, donc a échoué
}

void deadUnit(Unit* unit){
	// !!! unitAttack va appeler cette fonction
	unit = NULL;
	// On va appeler deadUnit(Unit* unit) lorsque la condition de succès d'attaque c'est confirmée
	// Unit* unit passé en paramètre va être l'unité attaquée
	// du coup on va convertir cette unité en pointeur sur NULL pour dire qu'elle pointera plus sur une unité
	// donc la case du tableau va afficher du vide
	// car dans board.c un pointeur sur NULL de type Unit affiche la case vide (lignes 16-21)
}

int main(){

	_world = (World*)malloc(sizeof(World));
	printf("move with WASD and press enter ...\n\n if you want to attack, press spacebar and enter");
	
	printf("Votre choix : %s\n", directionInput());

	displayBoard(world);
}