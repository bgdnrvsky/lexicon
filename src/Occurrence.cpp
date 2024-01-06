#include "Occurrence.h"
#include <cstring>

/**
 * @brief Initialise un tableau d'occurrences pour chaque lettre
 * @param[out] occurrences: tableau d'occurrences à initialiser
 */
void initialiser(Occurrences &occurrences) {
  // NOTE: occurrences = {0};

  for (unsigned i = 0; i < NOMBRE_LETTRES; ++i) {
    occurrences[i] = 0;
  }
}

/**
 * @brief Obtient le nombre d'occurrence d'une lettre
 * @param[in] occurrences: tableau d'occurrences a consulter
 * @param[in] lettre: lettre dont on cherche le nombre d'occurrences
 * @return  unsigned int : le nombre d'occurrences de la lettre
 */
unsigned int nombre_occurrences(Occurrences &occurrences, char lettre) {
  return occurrences[lettre - 'A'];
}

/**
 * @brief Retire une occurrence d'une lettre dans le tableau d'occurrences
 * @param[in,out] occurrences: tableau d'occurrences a modifier
 * @param[in] lettre: lettre pour laquelle on retire une occurrence
 */
void retirer_occurrence(Occurrences &occurrences, char lettre) {
  occurrences[lettre - 'A']--;
}

/**
 * @brief Ajoute une occurrence a une lettre dans le tableau d'occurrences
 * @param[in,out] occurrences : tableau d'occurrences a modifier
 * @param[in] lettre : lettre pour laquelle on ajoute une occurrence
 */
void ajouter_occurrence(Occurrences &occurrences, char lettre) {
  occurrences[lettre - 'A']++;
}

/**
 * @brief Compte le nombre d'occurences de chaque lettre dans la main
 * @param[in,out] occurrences: tableau d'occurrences a mettre a jour
 * @param[in] main : main de cartes a analyser
 * @see debut, estFin, suivant, lire et ajouter_occurrences
 */
void compter(Occurrences &occurrences, Main &main) {
  for (debut(main.cartes); !estFin(main.cartes); suivant(main.cartes))
    ajouter_occurrence(occurrences, lire(main.cartes).lettre);
}

void compter(Occurrences &occurrences, Mot &mot) {
  for (debut(mot); lire(mot).lettre != '\0'; suivant(mot))
    ajouter_occurrence(occurrences, lire(mot).lettre);
}

void compter(Occurrences &occurrences, const char mot[]) {
  for (unsigned i = 0; i < strlen(mot); ++i) {
    ajouter_occurrence(occurrences, mot[i]);
  }
}

void combiner(Occurrences &cible, const Occurrences &a, const Occurrences &b) {
  for (unsigned i = 0; i < NOMBRE_LETTRES; ++i) {
    cible[i] = a[i] + b[i];
  }
}
