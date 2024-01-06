#ifndef _PAQUET_H_
#define _PAQUET_H_

#include "Joueur.h"
#define CARTES_PAR_PAQUET 51
#define NOMBRE_LETTRES 26

/**
 * Nombre de cartes par lettre presentes dans le jeu avec leur valeur associee
 * Voir annexe
 * Format : {quantité, points}
 */
const int TOUTES_CARTES[NOMBRE_LETTRES][2] = {
    {2, 10}, {2, 2}, {2, 8}, {2, 6}, {5, 10}, {1, 2}, {2, 4}, {2, 8}, {4, 10},
    {1, 6},  {1, 8}, {2, 8}, {1, 8}, {3, 8},  {2, 8}, {1, 8}, {1, 4}, {3, 8},
    {3, 8},  {3, 8}, {3, 8}, {1, 8}, {1, 8},  {1, 2}, {1, 4}, {1, 2}};

#include "libs/Pile.h"

/**
 * @brief Structure de donnees representant un paquet de carte
 */
typedef Pile Paquet;

/**
 * @brief Remplit le paquet de cartes
 * @param[out] le paquet a remplir
 * @pre Le paquet doit etre initialise .
 * @see empiler
 */
void remplir(Paquet &paquet);

/**
 * @brief Distribue des cartes du paquet au joueur
 * @param[in,out] Le paquet contenant les cartes a distribuer
 * @param[in,out] Le joueur recevant les cartes
 * @pre Le joueur doit etre initialise
 * @see ajouter_carte, depiler
 */
void distribuer(Paquet &paquet, Joueur &joueur);

#endif
