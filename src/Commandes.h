#ifndef _COMMANDES_H_
#define _COMMANDES_H_

#include "Dictionnaire.h"
#include "Joueur.h"
#include "Mots.h"
#include "Paquet.h"

/**< Le status retourne par chaque commande */
enum Status { COMMANDE_INVALIDE, MOT_INEXISTANT, SUCCES };

/**
 * @brief Permet à un joueur piocher une carte du paquet et met une de ses
 * cartes sur le paquet de cartes exposees
 * @param[in,out] paquet: paquet de cartes a piocher
 * @param[in,out] joueur: joueur qui pioche
 * @param[in,out] exposees: paquet de cartes exposées
 * @see debut, estFin, suivant, lire, sommet, depiler, supprimer, empiler et
 * inserer
 */
Status piocher(std::istringstream &is, Paquet &paquet, Joueur &joueur,
               Paquet &exposees);

/**
 * @brief Permet à un joueur de poser un mot sur la chaine de mots poses
 * @param[in,out] joueur: joueur qui pose le mot
 * @param[in,out] mots: chaine de mots poses
 * @param[in,out] dictionnaire: dictionnaire de mots valides
 * @see debut, estFin, suivant, lire, sommet, depiler, supprimer, empiler et
 * inserer
 */
Status poser(std::istringstream &is, Joueur &joueur, Mots &mots,
             const Dictionnaire &dictionnaire);

/**
 * @brief Remplace un mot pose par un nouveau mot construit a partir de celui-ci
 * en y inserant des lettres par d'autres lettre detenues par le joueur
 * @param[in,out] joueur: le joueur qui effectue le remplacement
 * @param[in,out] mots: la chaine de mots poses ou se trouve le mot a remplacer
 */
Status remplacer(std::istringstream &is, Joueur &joueur, Mots &mots,
                 const Dictionnaire &dictionnaire);

/**
 * @brief Complète un mot pose par un nouveau mot construit a partir de celui-ci
 * en y inserant des lettres detenues par le joueur.
 * @param[in,out] joueur : le joueur qui complete le mot
 * @param[in,out] mots: la chaine de mots poses ou se trouve le mot a completer
 */
Status completer(std::istringstream &is, Joueur &joueur, Mots &mots,
                 const Dictionnaire &dictionnaire);

#endif
