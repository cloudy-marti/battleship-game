#define WIDTH 12
#define HEIGHT 18

#define RED 'R' // player 1
#define BLUE 'B' // player 2

#define SERVANT 's' // unit type
#define WARRIOR 'w'

typedef struct unit Unit;

typedef Unit* uList; // a type for the list

struct world World;