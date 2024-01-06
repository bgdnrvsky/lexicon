#ifndef _JOUEUR_H_
#define _JOUEUR_H_

#include "Hand.h"

/**
 * @struct Joueur
 * @brief Representation d'un joueur dans le jeu.
 */
typedef struct {
  unsigned int score; /**< Score du joueur dans le jeu. */
  Main main;          /**< Les cartes dont le joueur dispose. */
  bool est_perdant; /**< Indicateur de statut du joueur, vrai s'il est considere
                       comme perdant, sinon faux. */
} Joueur;

/**
 * @brief Calcule le score total du joueur en additionnant les valeurs des
 * cartes.
 * @param[in] joueur : le joueur dont on calcule le score
 * @see debut, estFin, suivant, lire
 * @return unsigned int : le score total du joueur après calcul
 */
unsigned int calculer_score(Joueur &joueur);

/**
 * @brief Initialise les données d'un joueur
 * @param[in,out] joueur: le joueur à initialiser
 * @see initialiser
 */
void initialiser(Joueur &joueur);

/**
 * @brief Affiche les lettres des cartes de la main du joueur
 * @param[in] joueur : le joueur dont on affiche les cartes
 * @see debut, estFin, suivant, lire
 */
void afficher_cartes(Joueur &joueur);

#endif
