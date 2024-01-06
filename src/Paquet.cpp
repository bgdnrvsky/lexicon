#include "Paquet.h"
#include "Hand.h"
#include <cassert>

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

void distribuer(Paquet &paquet, Joueur &joueur) {
  for (unsigned int i = 0; i < CARTES_PAR_JOUEUR; i++) {
    ajouter_carte(joueur.main, sommet(paquet));
    depiler(paquet);
  }
}
