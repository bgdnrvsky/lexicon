#include "../src/Dictionnaire.h"
#include "Tests.h"

GENERATE_TEST

bool test_valide(char *msg) {
  Dictionnaire d;

  REPORT_ATTENDU("Le dictionnaire a été initialisé");

  return initialiser(d, "tests/test_dict.txt");
}

bool test_invalide(char *msg) {
  Dictionnaire d;

  REPORT_ATTENDU("Le dictionnaire inexistant n'a pas été initialisé");

  return initialiser(d, "tests/invalid.txt");
}
