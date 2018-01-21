#include <stdio.h>
#include <stdlib.h>
#include "headers/typedefs.h"
#include "headers/unitManager.h"
#include "headers/playerManagerV2.h"

Unit* initializeUnit(char player, char type){
	Unit* unit = (Unit*)malloc(sizeof(Unit));
	// il y a toujours une étoile de plus dans le cast que dans le paramètre de sizeof
	// exemple : (Unit**)malloc(sizeof(Unit*))

	if(unit == NULL){
		exit(EXIT_FAILURE);
	}

	unit->player = player;
	unit->type = type;
	unit->isAlive = 1;
	// Assignation / affectation de valeur
	// convention imposée : la case mémoire qui va recevoir la valeur est à gauche
	// la valeur qui va être rangée dans la case mémoire est à droite
	unit->next = NULL;

	return unit;
}

void placeUnit(Unit* unit){
	// fonction qui va permettre au joueur de placer ses unités dans board
	// au début du jeu
	unit->posX = placeUnitInput('X', WIDTH);
	unit->posY = placeUnitInput('Y', HEIGHT);

	_world->board[unit->posX][unit->posY] = unit;
}

void placeAllUnit(){

	_world->blueList = playerPlaceUnits(BLUE, "blue");
	_world->redList = playerPlaceUnits(RED, "red");
}

Unit* playerPlaceUnits(char player, char* playerName){

	int i;

	char unitType[3] = {SERF, SERF, WARRIOR};
	char* unitTypeName[3] = {"serf", "serf", "warrior"};

	unitList list = NULL;
	// premier maillon de ma list, même si elle est nulle

	printf("the %s team must place their unit\n", playerName);
	for(i = 0; i < 3; ++i){
		Unit* newUnit = chooseUnit(player, unitType[i], unitTypeName[i]);
		list = addUnit(newUnit, list);
	}

	return list;
}

Unit* chooseUnit(char player, char type, char* typeName){

	Unit* unit = initializeUnit(player, type);
	printf("Place your %s ..\n", typeName);
	placeUnit(unit);

	return unit;
}

Unit* addUnit(Unit* newUnit, Unit* unit){

	if(newUnit == NULL){
		return unit;
		// si unit n'existe pas, newUnit est considéré le début de la liste
		// ce même si newUnit == NULL, parce que l'utilisateur de la fonction addUnit est censé
		// donner une newUnit non nulle
	}

	newUnit->next = unit;
	return newUnit;
	// je retourne le premier élément de la liste
}

void unitMove(Unit* unit, char* direction){ // unitManager

	int i;
	int translationX = 0;
	int translationY = 0;
	char* firstDirection = "";
	char* secondDirection = "";
	int switcher = 1;
	char* player = directionInput(direction);

	for(i = 0; player[i] != '\0'; i++){
		switch(player[i]){
			case('w') :
				--translationY;
				firstDirection = switcher ? "North" : firstDirection;
				secondDirection = switcher ? secondDirection : "North";
				break;
			case('s') :
				++translationY;
				firstDirection = switcher ? "South" : firstDirection;
				secondDirection = switcher ? secondDirection : "South";
				break;
			case('a'):
				--translationX;
				firstDirection = switcher ? "West" : firstDirection;
				secondDirection = switcher ? secondDirection : "West";
				break;
			case('d'):
				++translationX;
				firstDirection = switcher ? "East" : firstDirection;
				secondDirection = switcher ? secondDirection : "East";
				break;
			default :
				firstDirection = switcher ? "Nowhere..." : firstDirection;
				secondDirection = switcher ? secondDirection : "Nowhere...";
				break;
		}
		switcher = !switcher; 
	}

	printf("And so, their unit moved %s%s...\n", firstDirection, secondDirection[0] == firstDirection[0] ? "" : secondDirection);
	// Condition ternaire : (condition) ? code a executer si vrai, genre "si" : code a executer si faux, genre "else"
	// on peut enlever le break du case D parce que dans default il n'y a pas d'instructions.
	// le switch est comme une combinaison de for et de if. Le break sert à sortir du switch lorsque la condition a été faite

	Unit* tmpUnit = _world->board[unit->posX+translationX][unit->posY+translationY];
	// posX ou posY seuls ne sont pas déclarés ailleurs, donc j'ai changé par unit->posX/Y
	// car unit est mon pointeur sur mon Unit originale à la position posX/Y initiales

	// j'ai récupéré la case du tableau où le joueur veut aller
	// je la teste ci-dessous, car le joueur va pouvoir se déplacer ssi la case est vide

	// dans le cas où tmpUnit != NULL ->
	// unit passée en paramètre est l'unité qui va attaquer, et tmpUnit est l'unitée qui va prendre

	if(tmpUnit == NULL || !tmpUnit->isAlive){
		printf("Which they did successfully !\n");	
		_world->board[unit->posX+translationX][unit->posY+translationY] = unit;
		unit->posX += translationX;
		unit->posY += translationY;
		_world->board[unit->posX][unit->posY] = NULL;
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
		printf("But since there was somebody of their team already here, they've returned to their original place...\n");
		return;
	}
	// Ici on dit que si l'unité attaquée est de la même couleur (donc même équipe), on sort de la fonction attackUnit
	else if(unit->type == WARRIOR || tmpUnit->type == SERF){
		printf("They encountered an enemy ! And won the battle !\n");
		deadUnit(_world->board[unit->posX+translationX][unit->posY+translationY]);
		_world->board[unit->posX+translationX][unit->posY+translationY] = NULL;
		
	}
	else 
	{
		printf("They encountered an enemy ! And died miserably !\n");
		deadUnit(_world->board[unit->posX][unit->posY]);
		_world->board[unit->posX][unit->posY] = NULL;
	}
	// si je suis warrior OU mon enemi est un serf, l'enemi va mourrir
	// dans l'autre cas (serf vs warrior), je part de la fonction unitAttack
	// car le joueur a tenté d'attaquer une unité plus forte, donc a échoué

	return;
}

void deadUnit(Unit* unit){ // unitManager

	unit->isAlive = 0;
	unit->posX = -1;
	unit->posY = -1;
	// du coup on va donner comme condition qu'une unité morte aura pour valeur dans isAlive 0
	// donc la case du tableau va afficher du vide
	// car dans board.c un pointeur sur NULL de type Unit affiche la case vide
	// OU lorsque unit->isAlive == 0 (lignes 16-21)
}

void quitGame(char* directionInput){

	printf("you quit the game!\n");

	free(directionInput);
	directionInput = NULL;
	freeAll();

	exit(0);
}

void freeAll(){
	freeList(_world->redList);
	freeList(_world->blueList);

	free(_world);
	_world = NULL;
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