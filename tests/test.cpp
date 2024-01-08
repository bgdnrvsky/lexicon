#include "Tests.h"
#include <iostream>

void lancer_test(bool(test)(char *nom_teste, char *message_erreur)) {
  char nom_teste[TAILLE_MAX];
  char message_erreur[TAILLE_MAX];
  bool test_reussi = test(nom_teste, message_erreur);

  std::cout << nom_teste << " - ";

  if (test_reussi)
    std::cout << TEXTE_VERT << "Test réussi";
  else {
    std::cout << TEXTE_ROUGE << "Test échoué" << std::endl;

    // Afficher le message d'erreur
    std::cout << TEXTE_GRAS << "ERREUR: " << TEXTE_RESET << TEXTE_GRAS
              << message_erreur;
  }

  std::cout << TEXTE_RESET << std::endl;
}

int main() { lancer_test(test); }
