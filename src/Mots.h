#ifndef _MOTS_H_
#define _MOTS_H_

#include "libs/Chaine.h"

/**
 * @typedef Mots
 * @brief type representant la chaine de mots poses par les joueurs
 *        durant la partie.
 */
typedef Chaine Mots;

/**
 * @typedef Mot
 * @brief type representant un mot
 */
typedef Chaine Mot;

/**
 * @brief Affiche les mots poses
 * @param[in] mots : la chaine de mots poses par les joueurs
 * @see debut, estFin, suivant_mot, lire_mot, afficher
 */
void afficher_mots(Mots &mots);

/**
 * @brief Ajoute un mot à la chaine de mots poses
 * @param[in,out] mots: la chaine de mots poses a laquelle on ajoute le mot.
 * @param[in] mot : le mot a ajouter
 * @see debut, fin, estFin, suivant, inserer, lire et SPACER
 */
void ajouter_mot(Mots &mots, Mot &mot);

/**
 * @brief Deplace le curseur vers le mot suivant dans la chaine de mots poses par les joueurs.
 * @param[?] mots: la chaine de mots poses a parcourir.
 * @see estFin, suivant, lire, SPACER
 */
void suivant_mot(Mots &mots);

/**
 * @brief Lecture du mot stocke dans le maillon courant de la chaine de mots poses.
 * @param[in] mots: la chaine de mots poses ou se trouve le mot a lire
 * @param[?] mot : le mot ou sont stocke les informations lues
 */
void lire_mot(Mots &mots, Mot &mot);

/**
 * @brief Calcule la taille du mot
 * @param[in] mot: le mot dont on calcule la taille
 * @see estFin, lire, suivant, debut, SPACER
 * @return unsigned int : la taille du mot
 */
unsigned int taille_mot(Mot &mot);

/**
 * @brief Calcule le nombre de mots dans la chaine de mots poses par les joueurs.
 * @param[in] mots: la chaine de mots poses dont on calcule le nombre de mots
 * @see debut, estFin, suivant_mot
 * @return unsigned int : nombre de mots poses durant la partie
 */
unsigned int nombre_mots(Mots &mots);

/**
 * @brief Affiche le mot
 * @param[in] mot: le mot a afficher
 * @see estFin, lire, suivant
 */
void afficher(Mot &mot);

#endif
