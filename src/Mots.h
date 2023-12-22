#ifndef _MOTS_H_
#define _MOTS_H_

#include "libs/Chaine.h"

typedef Chaine Mots;
typedef Chaine Mot;

void ajouter_mot(Mots &mots, Mot &mot);
void suivant_mot(Mots &mots);
void lire_mot(Mots &mots, Mot &mot);
unsigned int taille_mot(Mot &mot);

#endif
