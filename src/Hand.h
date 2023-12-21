#ifndef _MAIN_H_
#define _MAIN_H_

#include "Carte.h"
#include "libs/Chaine.h"
#define CARTES_PAR_JOUEUR 10

typedef struct {
  Chaine cartes;
  unsigned int restantes; // Nombre de cartes restantes dans la main
} Main;

void ajouter_carte(Main &main, Carte carte);
void retirer_carte(Main &main);

#endif
