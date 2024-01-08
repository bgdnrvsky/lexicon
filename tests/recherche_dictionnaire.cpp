#include "../src/Dictionnaire.h"
#include "Tests.h"

GENERATE_TEST

bool test_valide(char *msg) {
  Dictionnaire d;

  initialiser(d, "tests/test_dict.txt");

  REPORT_MESSAGE("Les mot 'bonjour' et 'bonsoir' ont été trouvés");

  return rechercher(d, "bonjour") && rechercher(d, "bonsoir");
}

bool test_invalide(char *msg) {
  Dictionnaire d;

  initialiser(d, "tests/test_dict.txt");

  REPORT_MESSAGE("Le mot 'test' a été trouvé");

  return rechercher(d, "test");
}
