#include "src/Commandes.h"
#include "src/Dictionnaire.h"
#include "src/Hand.h"
#include "src/Joueur.h"
#include <iostream>
#include <sstream>

const char TEXTE_VERT[] = "\x1b[32;49m";
const char TEXTE_ROUGE[] = "\x1b[31;49m";
const char TEXTE_ITALIQUE[] = "\x1b[3m";
const char TEXTE_GRAS[] = "\x1b[1m";
const char TEXTE_RESET[] = "\x1b[0m";

#define POSITION                                                               \
  TEXTE_ROUGE << "\t\tEchec du test (" << __FUNCTION__ << ":" << __LINE__ << ")"

#define ASSERT(bool)                                                           \
  if (!bool) {                                                                 \
    std::cerr << std::endl << POSITION << TEXTE_RESET << std::endl;            \
    return;                                                                    \
  }

#define ASSERT_EQ(actual, expected)                                            \
  if (actual != expected) {                                                    \
    std::cerr << std::endl                                                     \
              << POSITION << ": " << TEXTE_RESET << TEXTE_ITALIQUE << expected \
              << " != " << actual << std::endl;                                \
    return;                                                                    \
  }

#define EXIT                                                                   \
  std::cout << " - " << TEXTE_VERT << "Succes" << TEXTE_RESET << std::endl;
#define INFO                                                                   \
  std::cout << "\tTest " << TEXTE_ITALIQUE << __FUNCTION__ << TEXTE_RESET

void initalisation_dictionnaire() {
  INFO;

  Dictionnaire d;

  ASSERT(initialiser(d, "ods4.txt"));

  EXIT
}

void manipulation_cartes() {
  INFO;

  Main m;
  initialiser(m);

  Carte a = nouvelle_carte('A'), b = nouvelle_carte('B'),
        c = nouvelle_carte('C');

  ASSERT_EQ(m.restantes, 0);

  ajouter_carte(m, a);
  ajouter_carte(m, b);

  ASSERT_EQ(m.restantes, 2);

  ASSERT(carte_existe(m, a));
  ASSERT(carte_existe(m, b));
  ASSERT(!carte_existe(m, c));

  debut(m.cartes);
  retirer_carte(m);

  ASSERT_EQ(m.restantes, 1);

  detruire(m);
  EXIT
}

void recherche_dictionnaire() {
  INFO;

  Dictionnaire d;
  ASSERT(initialiser(d, "ods4.txt"));

  ASSERT(rechercher(d, "BONJOUR"));
  ASSERT(rechercher(d, "BONSOIR"));
  ASSERT(!rechercher(d, "MOT_INEXISTANT"));

  EXIT
}

void test_joueur() {
  INFO;

  Joueur j;
  initialiser(j, 0);

  ASSERT(!j.est_perdant);
  ASSERT_EQ(j.id, 0);
  ASSERT_EQ(j.score, 0);
  ASSERT_EQ(j.tour_perdu, -1);

  Carte a = nouvelle_carte('A'), b = nouvelle_carte('B');

  ajouter_carte(j.main, a);
  ajouter_carte(j.main, b);

  j.score += calculer_score(j);

  ASSERT_EQ(j.score, a.valeur + b.valeur);

  detruire(j.main);
  EXIT
}

void test_poser() {
  INFO;

  Joueur j;
  initialiser(j, 1);

  Dictionnaire d;
  initialiser(d, "ods4.txt");

  Mots mots;
  initialiser(mots);

  Carte g = nouvelle_carte('G'), i = nouvelle_carte('I'),
        n = nouvelle_carte('N');

  ajouter_carte(j.main, g);
  ajouter_carte(j.main, i);
  ajouter_carte(j.main, n);

  // Cas 1: le mot peut etre pose sans probleme
  std::istringstream mot_valide("GIN");

  ASSERT_EQ(poser(mot_valide, j, mots, d), SUCCES);
  ASSERT_EQ(j.main.restantes, 0);

  Carte r = nouvelle_carte('R'), b = nouvelle_carte('B'),
        e = nouvelle_carte('E');

  ajouter_carte(j.main, r);
  ajouter_carte(j.main, b);
  ajouter_carte(j.main, e);

  // Cas 2: Le mot n'existe pas
  std::istringstream mot_inexistant("REB");

  ASSERT_EQ(poser(mot_inexistant, j, mots, d), MOT_INEXISTANT);
  ASSERT_EQ(j.main.restantes, 3);

  // Cas 3: le joueur ne peut pas construire le mot
  std::istringstream mot_joue_invalide("BARRE");

  ASSERT_EQ(poser(mot_joue_invalide, j, mots, d), COMMANDE_INVALIDE);

  detruire(j.main);
  EXIT
}

void test_remplacer() {
  INFO;

  Joueur j1;
  initialiser(j1, 1);

  Joueur j2;
  initialiser(j2, 2);

  Dictionnaire d;
  initialiser(d, "ods4.txt");

  Mots mots;
  initialiser(mots);

  Carte t = nouvelle_carte('T'), e = nouvelle_carte('E'),
        l = nouvelle_carte('L');

  ajouter_carte(j1.main, t);
  ajouter_carte(j1.main, e);

  ajouter_carte(j2.main, l);

  std::istringstream mot_orig("TE");
  poser(mot_orig, j1, mots, d);

  ASSERT_EQ(j1.main.restantes, 0);

  std::istringstream mot_valide_remplacant("1 LE");
  ASSERT_EQ(remplacer(mot_valide_remplacant, j2, mots, d), SUCCES);

  ASSERT_EQ(j2.main.restantes, 1);

  std::istringstream mot_invalide_remplacant("1 ME");
  ASSERT_EQ(remplacer(mot_invalide_remplacant, j2, mots, d), COMMANDE_INVALIDE);

  detruire(j1.main);
  detruire(j2.main);
  EXIT
}

int main(void) {
  std::cout << TEXTE_GRAS << "Lancement des tests" << TEXTE_RESET << std::endl;

  initalisation_dictionnaire();
  manipulation_cartes();
  recherche_dictionnaire();
  test_joueur();
  test_poser();
  test_remplacer();
}
