#include "Joueur.h"
#include "libs/Chaine.h"
#include <cstdio>

unsigned int calculer_score(Joueur &joueur) {
  unsigned int score = 0;

  for (debut(joueur.main.cartes); !estFin(joueur.main.cartes);
       suivant(joueur.main.cartes))
    score += lire(joueur.main.cartes).valeur;

  return score;
}

void initialiser(Joueur &joueur) {
  initialiser(joueur.main);
  joueur.score = 0;
  joueur.est_perdant = false;
}

void afficher_cartes(Joueur &joueur) {
  for (debut(joueur.main.cartes); !estFin(joueur.main.cartes);
       suivant(joueur.main.cartes)) {
    std::printf("%c", lire(joueur.main.cartes).lettre);
  }
}
