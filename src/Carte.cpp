#include "Carte.h"
#include "Paquet.h"

Carte nouvelle_carte(char lettre) {
  return (Carte){
      .lettre = lettre,
      .valeur = (unsigned)TOUTES_CARTES[lettre - 'A'][1],
  };
}
