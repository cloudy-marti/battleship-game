#include <stdlib.h>
#ifndef STRUCTURES__H
#define STRUCTURES__H

// ci-dessus ^
// ifndef = si STRUCTURES__H ( == structures.h) n'est pas défini
// define : tu le definis
// cela évitera le compilateur de relire 283472394 fois le header s'il est appelé dans plusieurs fichiers

#define WIDTH 12
#define HEIGHT 18

#define RED 'R' // player 1
#define BLUE 'B' // player 2

#define SERF 's' // unit type
#define WARRIOR 'w'

struct unit {
    int posX, posY; // x and y = coordinates in the game
    int isAlive; // if(isAlive == 0), mon unité est morte || if(isAlive == 1), mon unité est vivante
    char player; // red or blue    
    char type; // serf or warrior
    struct unit* next; // next unit on list    
};

// premier pointeur de ma liste chaînée

struct world {
    struct unit* board[WIDTH][HEIGHT]; // board of 12 x 18 squares
    int turn; // nb of turn
    struct unit* redList;
    struct unit* blueList; // units list for both players
};

/* je donne un surnom à World* */

struct world* _world;
//création d'une variable statique qui va pouvoir être rappelée dans toutes les fonctions créées

#endif
// on termine le if 