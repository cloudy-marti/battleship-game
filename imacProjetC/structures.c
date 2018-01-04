#include "shapes.h"

#define WIDTH 12
#define HEIGHT 18

#define RED 'R' // player 1
#define BLUE 'B' // player 2

#define SERVANT 's' // unit type
#define WARRIOR 'w'

struct unit {
    int posX, posY; // x and y = coordinates in the game
    char player; // red or blue    
    char type; // servant or warrior
    struct unit* next; // next unit on list    
};

typedef Unit* uList; // a type for the list

struct world {
    Unit *board[WIDTH][HEIGHT]; // board of 12 x 18 squares
    int turn; // nb of turn
    uList red, blue; // units list for both players
};