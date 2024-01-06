#include "Hand.h"
#include "Paquet.h"
#include "libs/Chaine.h"

/**
 * @brief Initialise la main d'un joueur
 * @param[in,out] main: reference vers la main du joueur
 * @see la fonction initaliser de Chaine.h
 */
void initialiser(Main &main) {
  initialiser(main.cartes);
  main.restantes = 0;
}

/**
 * @brief Detruit la main d'un joueur
 * @param[in,out]  main: reference vers la main du joueur
 * @see la fonction détruire de Chaine.H
 */
void detruire(Main &main) {
  detruire(main.cartes);
  main.restantes = 0;
}

/**
 * @brief Ajoute une carte a la main du joueur
 * @param[out] main: reference vers la main ou on insere la carte
 * @param[in] carte : carte inseree dans la main du joueur
 * @see inserer, suivant
 */
void ajouter_carte(Main &main, Carte carte) {
  inserer(main.cartes, carte);
  suivant(main.cartes);
  main.restantes++;
}

/**
 * @brief Retire la carte actuellement en tête de la main du joueur.
 * @param[in,out] main: la main du joueur
 * @see supprimer
 */
void retirer_carte(Main &main) {
  supprimer(main.cartes);
  main.restantes--;
}

/**
 * @brief Verifie la presence d'une carte dans la main du joueur
 * @param[in] main : la main du joueur
 * @param[in] carte : la carte a rechercher dans la main
 * @see debut, estFin, suivant, lire
 * @return vrai si la carte est presente dans la main, faux sinon.
 */
bool carte_existe(Main &main, Carte carte) {
  for (debut(main.cartes); !estFin(main.cartes); suivant(main.cartes)) {
    if (lire(main.cartes).lettre == carte.lettre) {
      return true;
    }
  }

  return false;
}

/**
 * @brief Retrouve une carte par sa lettre dans la main du joueur
 * @param[in] main : la main du joueur
 * @param[in] lettre: lettre de la carte a chercher
 * @param[out] carte : la carte a rechercher dans la main
 * @see debut, estFin, suivant, lire
 * @return vrai si la carte est trouvée, sinon faux.
 */
bool retrouver_carte_par_lettre(Main &main, char lettre, Carte &carte) {
  for (debut(main.cartes); !estFin(main.cartes); suivant(main.cartes)) {
    if (lire(main.cartes).lettre == lettre) {
      carte.lettre = lettre;
      carte.valeur = TOUTES_CARTES[lettre - 'A'][1];
      return true;
    }
  }

  return false;
}
