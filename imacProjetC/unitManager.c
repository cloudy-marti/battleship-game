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
	unit->isAlive = 1; // car l'unité créée est suposée vivante
	unit->next = NULL;
	// Assignation / affectation de valeur
	// convention imposée : la case mémoire qui va recevoir la valeur est à gauche
	// la valeur qui va être rangée dans la case mémoire est à droite

	return unit;
}

void placeUnit(Unit* unit){
	// fonction qui permet de ranger dans les cases posX et posY l'emplacement sur chaque axe rentré par le joueur
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
	// premier maillon de ma liste, même si elle est nulle

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
	int switcher = 1; // la valeur switch entre 0 et 1
	char* player = directionInput(direction);

	for(i = 0; player[i] != '\0'; i++){
		switch(player[i]){
			case('w') :
				--translationY; // wd
				firstDirection = switcher ? "North" : firstDirection;
				secondDirection = switcher ? secondDirection : "North";
				break;
				// = if(switcher == 1){ firstDirection == "North" }else{ firstDirection == firstDirection (donc on continue à parcourir le for)}
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
		// on considère switcher comme un booléen (entre 0 et 1)
		// toggle : quelque soit la valeur de switcher, on va l'inverser (switcher = 0) :
		// si elle est vrai on la rend fausse et vice-versa
	}

	printf("And so, their unit moved %s%s...\n", firstDirection, secondDirection);
	// Condition ternaire : (condition) ? code a executer si vrai, genre "si" : code a executer si faux, genre "else"
	// on peut enlever le break du case D parce que dans default il n'y a pas d'instructions.
	// le switch est comme une combinaison de for et de if. Le break sert à sortir du switch lorsque la condition a été faite

	Unit* tmpUnit = _world->board[unit->posX+translationX][unit->posY+translationY];
	// unit est mon pointeur sur mon Unit originale à la position posX/Y initiales

	// j'ai récupéré la case du tableau où le joueur veut aller
	// je la teste ci-dessous, car le joueur va pouvoir se déplacer que si la case est vide ou si l'unité qu'il y avait est morte

	// dans le cas où tmpUnit != NULL ->
	// unit passée en paramètre est l'unité qui va attaquer, et tmpUnit est l'unitée qui va prendre

	// on a enregistré la position du personnage et l'endroit où il veut attaquer
	// on gère le résultat ci-dessous

	if(tmpUnit == NULL || !tmpUnit->isAlive){ // isAlive == -1
		printf("Which they did successfully !\n");	
		_world->board[unit->posX][unit->posY] = NULL;
		_world->board[unit->posX+translationX][unit->posY+translationY] = unit;
		unit->posX += translationX; // ceci équivaut à unit->posX = posX + translationX
		unit->posY += translationY;
		// on demande à la position initiale de unit dans le tableau de pointer sur NULL
		// Le compilateur n'aurait rien dit, mais il y aurait une erreur de comportement : ce n'est pas ce qui est demandé
		// erreur de comportement : lorsque le joueur demanderais à ce déplacer, la même Unit se "doublerait" dans la case demandée

		// unit va être ensuite rangée dans une nouvelle case du tableau à partir de posX+translationX et posY+translationY
		// cela va permettre d'afficher unit dans la case correspondante, or unit->posX/Y n'est pas encore changé
		// donc on change posX/Y de unit juste après

		// Le tableau est constitué d'adresses sur unité
		// Lorsqu'il n'y a pas d'unité, la case pointe sur NULL
	}	
	else if(unit->player == tmpUnit->player){
		printf("But since there was already somebody of their team here, they've returned to their original place...\n");
		return;
	}
	// Ci-dessus on a dit que si l'unité attaquée est de la même couleur (donc même équipe), on sort de la fonction attackUnit
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
	// dans l'autre cas (serf vs warrior), je meur
	// car le joueur a tenté d'attaquer une unité plus forte, donc a échoué

	return;
}

void deadUnit(Unit* unit){ // unitManager

	unit->isAlive = 0;
	unit->posX = -1;
	unit->posY = -1;
	// du coup on va donner comme condition qu'une unité morte aura pour valeur 0 pour la variable isAlive
	// donc la case du tableau va afficher du vide
	// car dans board.c un pointeur sur NULL de type Unit affiche la case vide
	// OU lorsque unit->isAlive == 0 (board.c : lignes 16-21)
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
	// on a fait malloc pour allouer de la mémoire pour les unités de la liste quelque part
	// du coup on libère la mémoire
}