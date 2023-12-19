#include "Main.h"
#include "libs/Chaine.h"

void ajouter_carte(Main &main, Carte carte) {
  inserer(main.cartes, carte);
  suivant(main.cartes);
  main.restantes++;
}

void retirer_carte(Main *main) { main->restantes--; }
