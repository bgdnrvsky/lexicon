#include "Occurrence.h"
#include <cstring>

void initialiser(Occurrences &occurrences) {
  // NOTE: occurrences = {0};

  for (unsigned i = 0; i < NOMBRE_LETTRES; ++i) {
    occurrences[i] = 0;
  }
}

unsigned nombre_occurrences(Occurrences &occurrences, char lettre) {
  return occurrences[lettre - 'A'];
}

void retirer_occurrence(Occurrences &occurrences, char lettre) {
  occurrences[lettre - 'A']--;
}

void ajouter_occurrence(Occurrences &occurrences, char lettre) {
  occurrences[lettre - 'A']++;
}

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
