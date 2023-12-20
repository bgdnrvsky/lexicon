#include "Main.h"
#include "libs/Chaine.h"
#include <cassert>

void ajouter_carte(Main &main, Carte carte) {
  inserer(main.cartes, carte);
  suivant(main.cartes);
  main.restantes++;
}

void retirer_carte(Main &main) {
  assert(estFin(main.cartes));
  supprimer(main.cartes);
  main.restantes--;
}
