#include "../src/Joueur.h"
#include "Tests.h"

GENERATE_TEST

bool test_valide(char *msg) {
  Joueur j;
  initialiser(j, 0);

  REPORT_ATTENDU("Le joueur a ete initialise et son score est egale a 12")

  bool res = !j.est_perdant && j.id == 0 && j.score == 0 && j.tour_perdu == -1;

  Carte a = nouvelle_carte('A'), b = nouvelle_carte('B');

  ajouter_carte(j.main, a);
  ajouter_carte(j.main, b);

  j.score += calculer_score(j);

  res = res && j.score == (a.valeur + b.valeur);

  detruire(j.main);
  return res;
}

bool test_invalide(char *msg) {
  // Pas de test
  (void)msg;
  return false;
}
