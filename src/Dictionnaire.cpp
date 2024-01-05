#include "Dictionnaire.h"
#include "Paquet.h"
#include <cstring>
#include <fstream>
#include <iostream>

bool initialiser(Dictionnaire &dictionnaire, const char chemin[]) {
  std::ifstream fichier(chemin);
  dictionnaire.chemin = chemin;
  bool code = !!fichier;

  fichier.close();
  return code;
}

bool rechercher(Dictionnaire &dictionnaire, const char *mot) {
  std::ifstream fichier(dictionnaire.chemin);

  if (!fichier) {
    std::cerr << "Le dictionnaire n'a pas été initialisé" << std::endl;
    return false;
  }

  char mot_dictionnaire[NOMBRE_LETTRES];
  while (fichier >> mot_dictionnaire) {
    if (strcmp(mot_dictionnaire, mot) == 0) {
      fichier.close();
      return true;
    }
  }

  fichier.close();
  return false;
}
