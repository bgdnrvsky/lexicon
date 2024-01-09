#include "../src/Hand.h"
#include "Tests.h"

GENERATE_TEST

bool test_valide(char *msg) {
  Main m;
  initialiser(m);

  REPORT_ATTENDU("cartes 'A' et 'B' ont été trouvees");

  Carte a = nouvelle_carte('A'), b = nouvelle_carte('B');
  ajouter_carte(m, a);
  ajouter_carte(m, b);

  bool res = m.restantes == 2 && carte_existe(m, a) && carte_existe(m, b);

  Carte c;

  retrouver_carte_par_lettre(m, 'A', c);
  res = res && (c.lettre == a.lettre && c.valeur == a.valeur);

  retrouver_carte_par_lettre(m, 'B', c);
  res = res && (c.lettre == b.lettre && c.valeur == b.valeur);

  detruire(m);
  return res;
}

bool test_invalide(char *msg) {
  Main m;
  initialiser(m);

  REPORT_ATTENDU("La carte 'A' n'a pas été trouvée");

  Carte a = nouvelle_carte('A'), b = nouvelle_carte('B');
  ajouter_carte(m, a);
  ajouter_carte(m, b);

  debut(m.cartes);
  retirer_carte(m); // Retire la carte A

  bool res = carte_existe(m, a) && carte_existe(m, b);

  detruire(m);
  return res;
}
