#ifndef _MAIN_H_
#define _MAIN_H_

#include "libs/Chaine.h"
#define CARTES_PAR_JOUEUR 10

typedef struct {
  Chaine cartes;
  unsigned int restantes; // Nombre de cartes restantes dans la main
} Main;

void initialiser(Main &main);
void detruire(Main &main);
void ajouter_carte(Main &main, Carte carte);
void retirer_carte(Main &main);
bool carte_existe(Main &main, Carte carte);
bool retrouver_carte_par_lettre(Main &main, char lettre, Carte &carte);

#endif
