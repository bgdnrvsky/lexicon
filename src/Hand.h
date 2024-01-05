#ifndef _MAIN_H_
#define _MAIN_H_

#include "libs/Chaine.h"
#define CARTES_PAR_JOUEUR 10

/**
 * @struct Main
 * @brief Representation de la main d'un joueur.
 */

typedef struct {
    Chaine cartes;  /**< Chaîne représentant les cartes dans la main. */
    unsigned int restantes; /**< Nombre de cartes restantes dans la main */
} Main;

/**
 * @brief Initialise la main d'un joueur
 * @param[in,out] main: reference vers la main du joueur
 * @see la fonction initaliser de Chaine.h
 */
void initialiser(Main &main);

/**
 * @brief Detruit la main d'un joueur
 * @param[in,out]  main: reference vers la main du joueur
 * @see la fonction détruire de Chaine.H
 */
void detruire(Main &main);

/**
 * @brief Ajoute une carte a la main du joueur
 * @param[?] main: reference vers la main ou on insere la carte
 * @param[?] carte : carte inseree dans la main du joueur
 * @see inserer, suivant
 */
void ajouter_carte(Main &main, Carte carte);

/**
 * @brief Retire la carte actuellement en tête de la main du joueur.
 * @param[in,out] main: reference vers la main du joueur
 * @see supprimer
 */
void retirer_carte(Main &main);

/**
 * @brief Verifie la presence d'une carte dans la main du joueur
 * @param[?] main : reference vers la main du joueur
 * @param[?] carte : reference vers la carte a rechercher dans la main
 * @see debut, estFin, suivant, lire
 * @return vrai si la carte est presente dans la main, faux sinon.
 */
bool carte_existe(Main &main, Carte carte);

/**
 * @brief Retrouve une carte par sa lettre dans la main du joueur
 * @param[?] main : reference vers la main du joueur
 * @param[?] lettre: lettre de la carte a chercher
 * @param[out] carte : reference vers la carte a rechercher dans la main
 * @see debut, estFin, suivant, lire
 * @return vrai si la carte est trouvée, sinon faux.
 */
bool retrouver_carte_par_lettre(Main &main, char lettre, Carte &carte);

#endif
