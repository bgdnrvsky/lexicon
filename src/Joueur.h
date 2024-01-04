#ifndef _JOUEUR_H_
#define _JOUEUR_H_

#include "Hand.h"
typedef struct {
  unsigned int score;
  Main main; // Les cartes que le joueur dispose
  bool est_perdant;
} Joueur;

unsigned int calculer_score(Joueur &joueur);
void initialiser(Joueur &joueur);
void afficher_cartes(Joueur &joueur);

#endif
