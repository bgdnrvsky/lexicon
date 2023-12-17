#ifndef _JOUEUR_H_
#define _JOUEUR_H_

#include "Main.h"

typedef struct {
  unsigned int id;
  unsigned int score;
  Main main; // Les cartes que le joueur dispose
} Joueur;

#endif
