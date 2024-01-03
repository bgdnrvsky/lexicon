#ifndef _COMMANDES_H_
#define _COMMANDES_H_

#include "Joueur.h"
#include "Mots.h"
#include "Paquet.h"

// Chaque commande retourne true si la saisie etait valide
bool piocher(Paquet &paquet, Joueur &joueur, Paquet &exposees);
bool poser(Joueur &joueur, Mots &mots);
bool remplacer(Joueur &joueur, Mots &mots);
bool completer(Joueur &joueur, Mots &mots);

#endif
