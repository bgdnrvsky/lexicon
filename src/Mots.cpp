#include "Mots.h"
#include <iostream>

void ajouter_mot(Mots &mots, Mot &mot) {
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
  mot.tete = *mots.courant;
  mot.courant = mots.courant;
}

unsigned int taille_mot(Mot &mot) {
  unsigned int taille;
  for (taille = 0; !estFin(mot) && lire(mot).lettre != SPACER.lettre; suivant(mot))
    taille++;

  debut(mot);

  return taille;
}

void afficher(Mot &mot) {
    for (debut(mot); !estFin(mot) && lire(mot).lettre != '\0'; suivant(mot))
        std::cout << lire(mot).lettre;
}
