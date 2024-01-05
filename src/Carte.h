#ifndef _CARTE_H_
#define _CARTE_H_

/**
 * @struct Carte
 * @brief Representation d'une carte avec une lettre et une valeur.
 */
typedef struct {
  char lettre;         /**< Lettre associee a la carte. */
  unsigned int valeur; /**< Valeur associee a la carte. */
} Carte;

/**
 * @brief Carte spéciale représentant un espace.
 */
const Carte SPACER = (Carte){
    .lettre = '\0',
    .valeur = 0,
};

/**
 * @brief Cree une nouvelle carte a partir d'une lettre donnee
 * @param[in] lettre: lettre associee a la nouvelle carte
 * @return Carte: carte creee avec la lettre specifiee et la valeur associee
 */
Carte nouvelle_carte(char lettre);

#endif
