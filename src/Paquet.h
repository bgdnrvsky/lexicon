#ifndef _PAQUET_H_
#define _PAQUET_H_

#include "libs/Pile.h"
#define CARTES_PAR_PAQUET 51

// Voir annexe
// Format : {quantité, points}
const int TOUTES_CARTES[][2] = {
    {2, 10}, {2, 2}, {2, 8}, {2, 6}, {5, 10}, {1, 2}, {2, 4}, {2, 8}, {4, 10},
    {1, 6},  {1, 8}, {2, 8}, {1, 8}, {3, 8},  {2, 8}, {1, 8}, {1, 4}, {3, 8},
    {3, 8},  {3, 8}, {3, 8}, {1, 8}, {1, 8},  {1, 2}, {1, 4}, {1, 2}};

typedef Pile Paquet;

void remplir(Paquet& paquet);

#endif
