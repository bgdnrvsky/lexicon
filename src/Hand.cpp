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
 * @param[?] main: reference vers la main ou on insere la carte
 * @param[?] carte : carte inseree dans la main du joueur
 * @see inserer, suivant
 */
void ajouter_carte(Main &main, Carte carte) {
  inserer(main.cartes, carte);
  suivant(main.cartes);
  main.restantes++;
}

void retirer_carte(Main &main) {
  supprimer(main.cartes);
  main.restantes--;
}

bool carte_existe(Main &main, Carte carte) {
    for (debut(main.cartes); !estFin(main.cartes); suivant(main.cartes)) {
        if (lire(main.cartes).lettre == carte.lettre) {
            return true;
        }
    }

    return false;
}

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
