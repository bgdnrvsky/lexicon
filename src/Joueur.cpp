#include "Joueur.h"
#include "libs/Chaine.h"
#include <cstdio>

/**
 * @brief Calcule le score total du joueur en additionnant les valeurs des
 * cartes.
 * @param[in] joueur : le joueur dont on calcule le score
 * @see debut, estFin, suivant, lire
 * @return unsigned int : le score total du joueur après calcul
 */
unsigned int calculer_score(Joueur &joueur) {
  unsigned int score = 0;

  for (debut(joueur.main.cartes); !estFin(joueur.main.cartes);
       suivant(joueur.main.cartes))
    score += lire(joueur.main.cartes).valeur;

  return score;
}

/**
 * @brief Initialise les données d'un joueur
 * @param[in,out] joueur: le joueur à initialiser
 * @see initialiser
 */
void initialiser(Joueur &joueur) {
  initialiser(joueur.main);
  joueur.score = 0;
  joueur.est_perdant = false;
}

/**
 * @brief Affiche les lettres des cartes de la main du joueur
 * @param[in] joueur : le joueur dont on affiche les cartes
 * @see debut, estFin, suivant, lire
 */
void afficher_cartes(Joueur &joueur) {
  for (debut(joueur.main.cartes); !estFin(joueur.main.cartes);
       suivant(joueur.main.cartes)) {
    std::printf("%c", lire(joueur.main.cartes).lettre);
  }
}
