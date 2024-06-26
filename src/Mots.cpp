#include "Mots.h"
#include <iostream>

void afficher_mots(Mots &mots) {
  unsigned int i = 1;
  for (debut(mots); !estFin(mots); suivant_mot(mots)) {
    Mot mot;
    lire_mot(mots, mot);

    std::cout << i << " - ";

    afficher(mot);

    std::cout << std::endl;

    i++;
  }
}

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
  for (taille = 0; !estFin(mot) && lire(mot).lettre != SPACER.lettre;
       suivant(mot))
    taille++;

  debut(mot);

  return taille;
}

unsigned nombre_mots(Mots &mots) {
  unsigned int nombre_mots = 0;
  for (debut(mots); !estFin(mots); suivant_mot(mots))
    nombre_mots++;

  debut(mots);
  return nombre_mots;
}

void afficher(Mot &mot) {
  for (debut(mot); !estFin(mot) && lire(mot).lettre != '\0'; suivant(mot))
    std::cout << lire(mot).lettre;
}
