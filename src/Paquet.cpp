#include "Paquet.h"
#include "Hand.h"
#include <cassert>

/**
 * @brief Remplit le paquet de cartes
 * @param[out] paquet:le paquet a remplir
 * @pre Le paquet doit etre initialise .
 * @see empiler
 */
void remplir(Paquet &paquet) {
  unsigned int nombre_total = 0; // Nombre total de cartes dans le paquet
  for (unsigned int i = 0; i < 26; i++) {
    char lettre = i + 'A';
    unsigned int quantite = TOUTES_CARTES[i][0];
    unsigned int points = TOUTES_CARTES[i][1];
    nombre_total += quantite;

    for (unsigned int j = 0; j < quantite; j++) {
      Carte carte = {lettre, points};
      empiler(paquet, carte);
    }
  }

  assert(nombre_total == CARTES_PAR_PAQUET);
}

/**
 * @brief Distribue des cartes du paquet au joueur
 * @param[in,out] paquet:  le paquet contenant les cartes a distribuer
 * @param[in,out] joueur: le joueur recevant les cartes
 * @pre le joueur doit etre initialise
 * @see ajouter_carte, depiler
 */
void distribuer(Paquet &paquet, Joueur &joueur) {
    for (unsigned int i = 0; i < CARTES_PAR_JOUEUR; i++) {
        ajouter_carte(joueur.main, sommet(paquet));
        depiler(paquet);
    }
}
