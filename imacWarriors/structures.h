#include <stdio.h>
#include <stdlib.h>

#define WIDTH 12
#define HEIGHT 18

#define RED 'R' // player 1
#define BLUE 'B' // player 2

#define SERVANT 's' // unit type
#define WARRIOR 'w'

typedef struct unit {
    int posX, posY; // x and y = coordinates in the game
    char player; // red or blue    
    char type; // servant or warrior
    struct unit *next; // next unit on list    
} Unit;

struct world {
    
}