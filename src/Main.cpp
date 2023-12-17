#include "Main.h"

void ajouter_carte(Main *main, Carte carte) {
  main->cartes[main->restantes++] = carte;
}

void retirer_carte(Main *main) { main->restantes--; }
