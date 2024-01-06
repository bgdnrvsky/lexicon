#include "Carte.h"
#include "Paquet.h"

Carte nouvelle_carte(char lettre) {
  return (Carte){
      .lettre = lettre,
      .valeur = (unsigned)
          TOUTES_CARTES[lettre - 'A'][1], // Valeur associee a la nouvelle carte
                                          // en fonction de la lettre
  };
}
