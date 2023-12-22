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

void suivant_mot(Mots &mots) {
  for (; !estFin(mots) && lire(mots).lettre != SPACER.lettre; suivant(mots))
    continue;
  suivant(mots);
}

void lire_mot(Mots &mots, Mot &mot) {
  mot.longueur = 0;
  mot.tete = *mots.courant;
  mot.courant = mots.courant;
}

unsigned int taille_mot(Mot &mot) {
  unsigned int taille;
  for (taille = 0; lire(mot).lettre != SPACER.lettre; suivant(mot))
    taille++;

  return taille;
}
