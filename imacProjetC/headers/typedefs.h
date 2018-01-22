#pragma once
#include "structures.h"
typedef struct unit Unit;
typedef Unit* unitList; // premier pointeur de ma liste chaînée
typedef struct world World;
typedef World* p_World;

// ceci permet d'éviter l'inclusion en diamand

// On renomme avec typedef les structures qu'on a défini dans structures.h
// ça a permit d'éviter l'inclusion en diamand

// mais pourquoi ?? 