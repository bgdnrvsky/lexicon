#ifndef _OCCURRENCE_H_
#define _OCCURRENCE_H_

#include "Mots.h"
#include "Paquet.h"

/**
 * @brief Type representant un tableau d'occurrences pour chaque lettre
 */
typedef unsigned Occurrences[NOMBRE_LETTRES];

/**
 * @brief Initialise un tableau d'occurrences pour chaque lettre
 * @param[out] occurrences: tableau d'occurrences à initialiser
 */
void initialiser(Occurrences &occurrences);

/**
 * @brief Obtient le nombre d'occurrence d'une lettre
 * @param[in] occurrences: tableau d'occurrences a consulter
 * @param[in] lettre: lettre dont on cherche le nombre d'occurrences
 * @return  unsigned int : le nombre d'occurrences de la lettre
 */
unsigned int nombre_occurrences(Occurrences &occurrences, char lettre);

/**
 * @brief Retire une occurrence d'une lettre dans le tableau d'occurrences
 * @param[in,out] occurrences: tableau d'occurrences a modifier
 * @param[in] lettre: lettre pour laquelle on retire une occurrence
 */
void retirer_occurrence(Occurrences &occurrences, char lettre);

/**
 * @brief Ajoute une occurrence a une lettre dans le tableau d'occurrences
 * @param[in,out] occurrences : tableau d'occurrences a modifier
 * @param[in] lettre : lettre pour laquelle on ajoute une occurrence
 */
void ajouter_occurrence(Occurrences &occurrences, char lettre);

/**
 * @brief Compte le nombre d'occurences de chaque lettre dans la main
 * @param[in,out] occurrences: tableau d'occurrences a mettre a jour
 * @param[in] main : main de cartes a analyser
 * @see debut, estFin, suivant, lire ajouter_occurrences
 */
void compter(Occurrences &occurrences, Main &main);

void compter(Occurrences &occurrences, Mot &mot);

void compter(Occurrences &occurrences, const char mot[]);

void combiner(Occurrences &cible, const Occurrences &a, const Occurrences &b);

#endif
