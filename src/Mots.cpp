#include "Mots.h"

void ajouter_mot(Mots &mots, Chaine &mot) {
  fin(mots);
  for (debut(mot); !estFin(mot); suivant(mot)) {
    inserer(mots, lire(mot));
    suivant(mots);
  }

  inserer(mots, SPACER);
  suivant(mots);
}
