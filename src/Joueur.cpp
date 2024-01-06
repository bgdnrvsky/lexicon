#include "Joueur.h"
#include "libs/Chaine.h"
#include <algorithm>
#include <cstdio>
#include <iostream>

unsigned int calculer_score(Joueur &joueur) {
  unsigned int score = 0;

  for (debut(joueur.main.cartes); !estFin(joueur.main.cartes);
       suivant(joueur.main.cartes))
    score += lire(joueur.main.cartes).valeur;

  return score;
}

void initialiser(Joueur &joueur, unsigned int id) {
  initialiser(joueur.main);
  joueur.score = 0;
  joueur.est_perdant = false;
  joueur.tour_perdu = -1;
  joueur.id = id;
}

void afficher_cartes(Joueur &joueur) {
  for (debut(joueur.main.cartes); !estFin(joueur.main.cartes);
       suivant(joueur.main.cartes)) {
    std::printf("%c", lire(joueur.main.cartes).lettre);
  }
}

void afficher_scores(const Joueur *joueurs, unsigned int nombre_joueurs,
                     unsigned int tour_actuel) {
  unsigned int **scores =
      new unsigned int *[nombre_joueurs]; // Format: [id, score]

  // On copie les scores
  for (unsigned int i = 0; i < nombre_joueurs; i++) {
    scores[i] = new unsigned int[2];

    scores[i][0] = joueurs[i].id;
    scores[i][1] = joueurs[i].score;
  }

  // On trie les scores par scores[i][1]
  std::sort(scores, scores + nombre_joueurs,
            [](const auto &a, const auto &b) { return a[1] < b[1]; });

  // On affiche les scores
  std::cout << "* Scores" << std::endl;

  for (unsigned int i = 0; i < nombre_joueurs; i++) {
    Joueur joueur = joueurs[scores[i][0]];

    if (joueur.est_perdant && joueur.tour_perdu < (int)tour_actuel)
      // Le joueur avait perdu avant ce tour, donc on n'affiche pas son score
      continue;

    std::printf("Joueur %u : %u points\n", joueur.id + 1, joueur.score);
  }

  for (unsigned int i = 0; i < nombre_joueurs; i++)
    delete[] scores[i];

  delete[] scores;
}
