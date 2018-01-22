
#include "headers/turnManager.h"

int main(){

    initializeGame();
    manageTurn(); 
    
    return 0;
}

// dans game.c on include que le fichier contenant les fonctions qui vont composer le jeu
// ces fonctions contiennent elles-mêmes les fonctions de tous les autres fichiers