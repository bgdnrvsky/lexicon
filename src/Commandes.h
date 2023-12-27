#ifndef _COMMANDES_H_
#define _COMMANDES_H_

#include "Joueur.h"
#include "Mots.h"
#include "Paquet.h"

void piocher(Paquet &paquet, Joueur &joueur, Paquet &exposees);
void poser(Joueur &joueur, Mots &mots);
void remplacer(Joueur &joueur, Mots &mots);

#endif
