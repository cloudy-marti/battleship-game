#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

char* getInput(){

    int i;
    const int taille = 3;    
    char player[taille] = {'0', '0', '\0'};

    printf("move with WASD and press enter\n");
    
    while(checkInput(player) == -1){
        scanf("%s", &player);
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

    // ww cas d'erreur -> le faire

    return 0; // si ya pas de cas d'erreurs, je retourne 0
}

void unitMove(Unit unit){

    //quand est-ce qu'on appelle getInput ??
    // pas ce switch case -> mes entrees sont forcement valides
    //switch case quand meme
    // w -> vers 0 donc posY--


    //switch -> https://www.tutorialspoint.com/cprogramming/switch_statement_in_c.htm
    //sinon if / if else /if else / etc ?
    switch(player){
        case("w" || "W") :
            unit->posY++;
            break;
        case("a" || "A") :
            unit->posX--;
            break;
        case("s" || "S"):
            unit->posY--;
            break;
        case("d" || "D") :
            unit->posX++;
            break;
        case("wa" || "Wa" || "wA" || "WA" || "aw" || "Aw" || "aW" || "AW") :
            unit->posX--;
            unit->posY++;
            break;
        case(wd || Wd || wD || WD || dw || Dw || dW || DW) :
            unit->posX++;
            unit->posY++;
            break;
        case(sa || Sa || sA || SA || as || As || aS || AS) :
            unit->posX--;
            unit->posY--;
            break;
        case(sd || Sd || sD || SD || ds || Ds || dS || DS) :
            unit->posX++;
            unit->posY--;
            break;
        default :
            printf("wtf"); // je veux revenir au scanf sans devoir le retaper
    }

}

int main(){

	pWorld world = (World*)malloc(sizeof(World));

	displayBoard(world);
}
