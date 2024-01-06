#include "Mots.h"
#include <iostream>

/**
 * @brief Affiche les mots poses
 * @param[in] mots : la chaine de mots poses par les joueurs
 * @see debut, estFin, suivant_mot, lire_mot, afficher
 */
void afficher_mots(Mots &mots) {
  unsigned int i = 1;
  for (debut(mots); !estFin(mots); suivant_mot(mots)) {
    Mot mot;
    lire_mot(mots, mot);

    std::cout << i << " - ";

    afficher(mot);

    std::cout << std::endl;

    i++;
  }
}

/**
 * @brief Ajoute un mot à la chaine de mots poses
 * @param[in,out] mots: la chaine de mots poses a laquelle on ajoute le mot.
 * @param[in] mot : le mot a ajouter
 * @see debut, fin, estFin, suivant, inserer, lire et SPACER
 */
void ajouter_mot(Mots &mots, Mot &mot) {
  fin(mots);

  for (debut(mot); !estFin(mot); suivant(mot)) {
    inserer(mots, lire(mot));
    suivant(mots);
  }

  inserer(mots, SPACER);
  suivant(mots);
}

/**
 * @brief Deplace le curseur vers le mot suivant dans la chaine de mots poses
 * par les joueurs.
 * @param[in, out] mots: la chaine de mots poses a parcourir.
 * @see estFin, suivant, lire, SPACER
 */
void suivant_mot(Mots &mots) {
  for (; !estFin(mots) && lire(mots).lettre != SPACER.lettre; suivant(mots))
    continue;
  suivant(mots);
}

/**
 * @brief Lecture du mot stocke dans le maillon courant de la chaine de mots
 * poses.
 * @param[in] mots: la chaine de mots poses ou se trouve le mot a lire
 * @param[out] mot : le mot ou sont stockes les informations lues
 */
void lire_mot(Mots &mots, Mot &mot) {
  mot.tete = *mots.courant;
  mot.courant = mots.courant;
}

/**
 * @brief Calcule la taille du mot
 * @param[in] mot: le mot dont on calcule la taille
 * @see estFin, lire, suivant, debut, SPACER
 * @return unsigned int : la taille du mot
 */
unsigned int taille_mot(Mot &mot) {
  unsigned int taille;
  for (taille = 0; !estFin(mot) && lire(mot).lettre != SPACER.lettre;
       suivant(mot))
    taille++;

  debut(mot);

  return taille;
}

/**
 * @brief Calcule le nombre de mots dans la chaine de mots poses par les
 * joueurs.
 * @param[in] mots: la chaine de mots poses dont on calcule le nombre de mots
 * @see debut, estFin, suivant_mot
 * @return unsigned int : nombre de mots poses durant la partie
 */
unsigned nombre_mots(Mots &mots) {
  unsigned int nombre_mots = 0;
  for (debut(mots); !estFin(mots); suivant_mot(mots))
    nombre_mots++;

  debut(mots);
  return nombre_mots;
}

/**
 * @brief Affiche le mot
 * @param[in] mot: le mot a afficher
 * @see estFin, lire, suivant
 */
void afficher(Mot &mot) {
  for (debut(mot); !estFin(mot) && lire(mot).lettre != '\0'; suivant(mot))
    std::cout << lire(mot).lettre;
}
