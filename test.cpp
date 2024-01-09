#include "src/Dictionnaire.h"
#include "src/Hand.h"
#include "src/Joueur.h"
#include "src/Commandes.h"
#include <iostream>

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

#define SUCCES                                                                 \
  std::cout << " - " << TEXTE_VERT << "Succes" << TEXTE_RESET << std::endl;
#define INFO                                                                   \
  std::cout << "\tTest " << TEXTE_ITALIQUE << __FUNCTION__ << TEXTE_RESET

void initalisation_dictionnaire() {
  INFO;

  Dictionnaire d;

  ASSERT(initialiser(d, "ods4.txt"));

  SUCCES
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
  SUCCES
}

void recherche_dictionnaire() {
  INFO;

  Dictionnaire d;
  ASSERT(initialiser(d, "ods4.txt"));

  ASSERT(rechercher(d, "BONJOUR"));
  ASSERT(rechercher(d, "BONSOIR"));
  ASSERT(!rechercher(d, "MOT_INEXISTANT"));

  SUCCES
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
  SUCCES
}

void test_poser(){
	INFO;

	Joueur j1;
	initialiser(j1, 1);
	Dictionnaire d;
	initialiser(d, "ods4.txt");
	Mots mots;

	Carte g = nouvelle_carte('G'), i = nouvelle_carte('I'), n = nouvelle_carte('N');
	ajouter_carte(j1.main,g);
	ajouter_carte(j1.main,i);
	ajouter_carte(j1.main,n);

	char mot_valide[] ="GIN";
	std::istringstream mot_joue(mot_valide);
	Status result =poser(mot_joue,j1,mots,d);
	ASSERT_EQ(result,SUCCES);

	detruire(j1.main);
	SUCCES
}


int main(void) {
  std::cout << TEXTE_GRAS << "Lancement des tests" << TEXTE_RESET << std::endl;

  initalisation_dictionnaire();
  manipulation_cartes();
  recherche_dictionnaire();
  test_joueur();
	test_poser();
}
