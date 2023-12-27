#include "Commandes.h"
#include "Joueur.h"
#include "Mots.h"
#include "Paquet.h"
#include "libs/Vec.h"
#include <iostream>

#define MAX_NOMBRE_JOUEURS 4

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <nombre_joueurs>" << std::endl;
    return 1;
  }

  int nombre_joueurs = atoi(argv[1]);
  if (nombre_joueurs <= 1 || nombre_joueurs > MAX_NOMBRE_JOUEURS) {
    std::cout << "Le nombre de joueurs doit être compris entre 2 et "
              << MAX_NOMBRE_JOUEURS << std::endl;
    return 1;
  }

  Joueur joueurs[MAX_NOMBRE_JOUEURS];

  for (unsigned int i = 0; i < (unsigned int)nombre_joueurs; i++) {
    Joueur &joueur = joueurs[i];
    initialiser(joueur.main);
    joueur.score = 0;
  }

  Paquet paquet;

  initialiser(paquet, CARTES_PAR_PAQUET);
  remplir(paquet);

  melanger(paquet.tab, CARTES_PAR_PAQUET);

  // Distribuer les cartes aux joueurs
  for (unsigned int i = 0; i < (unsigned int)nombre_joueurs; i++)
    distribuer(paquet, joueurs[i]);

  Paquet exposees; // Les cartes exposées
  initialiser(exposees, CARTES_PAR_PAQUET);

  // Exposer la première carte du paquet
  empiler(exposees, sommet(paquet));
  depiler(paquet);

  std::cout << "(Commandes valides : TEPRC)" << std::endl << std::endl;

  Mots mots;
  initialiser(mots);

  // Commencer le jeu
  unsigned int joueur_id = 0;
  bool a_quitter = false;
  while (nombre_joueurs >= 2) {
    Joueur *joueur = &joueurs[joueur_id];

    std::printf("* Joueur %d (%c) ", joueur_id + 1, sommet(exposees).lettre);

    for (debut(joueur->main.cartes); !estFin(joueur->main.cartes);
         suivant(joueur->main.cartes)) {
      std::printf("%c", lire(joueur->main.cartes).lettre);
    }
    std::cout << std::endl;

    // Lister tous les mots
    unsigned int i = 1;
    for (debut(mots); !estFin(mots); suivant_mot(mots)) {
      Mot mot;
      lire_mot(mots, mot);

      std::cout << i << " - ";

      afficher(mot);

      std::cout << std::endl;

      i++;
    }

    std::cout << "> ";

    char commande;
    std::cin >> commande;

    switch (commande) {
    case 'T':
      // Talon
      piocher(paquet, *joueur, exposees);
      break;
    case 'E':
      // Exposées
      piocher(exposees, *joueur, exposees);
      break;
    case 'P':
      // Poser
      poser(*joueur, mots);
      break;
    case 'R':
      remplacer(*joueur, mots);
      // Remplacer
      break;
    case 'C':
      // Completer
      break;
    case 'Q':
      a_quitter = true;
      break;
    default:
      // TODO: Recommencer la saisie au cas où la commande est invalide
      std::cout << "Commande invalide" << std::endl;
    }

    if (a_quitter)
      break;

    joueur_id = (joueur_id + 1) % nombre_joueurs;
  }

  detruire(mots);
  detruire(paquet);
  detruire(exposees);

  for (unsigned int i = 0; (int)i < nombre_joueurs; i++)
    detruire(joueurs[i].main.cartes);

  return 0;
}
