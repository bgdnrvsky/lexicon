#ifndef _CONTENEURTDE_
#define _CONTENEURTDE_
/**
 * @file Vec.cpp
 * Projet sem04-tp-Cpp1-3
 * @author l'équipe pédagogique
 * @version 2 - 29/11/2014
 * @brief corrige du TD n°3 sur machine - Exercice 2
 * Structures de données et algorithmes - DUT1 Paris Descartes
 */

#include "Item.h"

/**
 * @brief Conteneur d'items (tableau dynamique)
 */
typedef struct {
  unsigned int capacite;     ///< Capacité du conteneur
  unsigned int len;          ///< Nombre d'items dans le conteneur
  unsigned int pasExtension; ///< Pas d'extension de capacité
  Item *tab;                 ///< Tableau dynamique d'items
} Vec;

/**
 * @brief Initialise un conteneur d'items
 * Allocation en mémoire dynamique du conteneur d'items
 * de capacité (capa) extensible par pas d'extension (p)
 * @see detruire, pour sa désallocation en fin d'utilisation
 * @param[out] vec : le conteneur d'items
 * @param [in] cap : capacité du conteneur
 * @pre capa>0
 */
void initialiser(Vec &vec, unsigned int cap);

/**
 * @brief Désalloue un conteneur d'items en mémoire dynamique
 * @see initialiser, le conteneur d'items a déjà été alloué
 * @param[out] vec : le conteneur d'items
 */
void detruire(Vec &vec);

/**
 * @brief Lecture d'un item d'un conteneur d'items
 * @param[in] vec : le conteneur d'items
 * @param[in] pos : la position de l'item dans le conteneur
 * @return l'item à la position i
 * @pre i < c.capacite
 */
Item lire(const Vec &vec, unsigned int pos);

/**
 * @brief Ecrire un item dans un conteneur d'items
 * @param[in,out] vec : le conteneur d'items
 * @param[in] pos : la position où ajouter/modifier l'item
 * @param[in] it : l'item à écrire
 */
void ecrire(Vec &vec, unsigned int pos, const Item &it);

/**
 * @brief Melanger le contenu de liste
 * @param[in,out] tab : le tableau d'items
 * @param[in] nb : nombre d'items dans le tableau
 */
void melanger(Item *tab, unsigned int nb);

#endif
