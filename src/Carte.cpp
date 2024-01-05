#include "Carte.h"
#include "Paquet.h"

/**
 * @brief Cree une nouvelle carte a partir d'une lettre donnee.
 * @param[in] lettre: Lettre associee a la nouvelle carte.
 * @note La fonction utilise la liste TOUTES_CARTES pour obtenir la valeur associee a la lettre.
 * @return Carte : Nouvelle carte creee avec la lettre specifiee et sa valeur associee.
 */
Carte nouvelle_carte(char lettre) {
  return (Carte){
      .lettre = lettre,
      .valeur = (unsigned)TOUTES_CARTES[lettre - 'A'][1], /**< Valeur associee a la nouvelle carte en fonction de la lettre */
  };
}
