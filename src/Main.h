#ifndef _MAIN_H_
#define _MAIN_H_

#include "Carte.h"
#define CARTES_PAR_JOUEUR 10

typedef struct {
  Carte cartes[CARTES_PAR_JOUEUR];
  unsigned int restantes; // Nombre de cartes restantes dans la main
} Main;

void ajouter_carte(Main *main, Carte carte);
void retirer_carte(Main *main);

#endif
