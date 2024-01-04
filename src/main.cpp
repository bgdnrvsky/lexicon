#include "Commandes.h"
#include "Joueur.h"
#include "Mots.h"
#include "Paquet.h"
#include "libs/Vec.h"
#include <climits>
#include <iostream>

#define MAX_NOMBRE_JOUEURS 4

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Utilisation: " << argv[0] << " <nombre_joueurs>" << std::endl;
    return 1;
  }

  int nombre_joueurs = atoi(argv[1]);
  if (nombre_joueurs <= 1 || nombre_joueurs > MAX_NOMBRE_JOUEURS) {
    std::cout << "Le nombre de joueurs doit être compris entre 2 et "
              << MAX_NOMBRE_JOUEURS << std::endl;
    return 1;
  }

  std::cout << "(Commandes valides : TEPRC)" << std::endl << std::endl;

  Joueur joueurs[MAX_NOMBRE_JOUEURS];

  for (unsigned int i = 0; i < (unsigned int)nombre_joueurs; i++)
    initialiser(joueurs[i]);

  unsigned int nombre_joueurs_actifs =
      nombre_joueurs; // Nombre de joueurs qui sont toujours en jeu

  bool reinitilisation =
      true; // Lorsque le premier ou nouveau tour on initialise les objets

  Paquet paquet;
  Paquet exposees; // Les cartes exposées
  Mots mots;       // Les mots poses

  unsigned int joueur_id; // ID du joueur qui joue

  for (joueur_id = 0; nombre_joueurs_actifs > 1;
       joueur_id = (joueur_id + 1) % nombre_joueurs) {
    if (reinitilisation) {
      joueur_id = 0;

      initialiser(paquet, CARTES_PAR_PAQUET);
      initialiser(exposees, CARTES_PAR_PAQUET);
      initialiser(mots);

      remplir(paquet);
      melanger(paquet.tab, CARTES_PAR_PAQUET);

      // Distribuer les cartes aux joueurs
      for (unsigned int i = 0; i < (unsigned int)nombre_joueurs; i++)
        distribuer(paquet, joueurs[i]);

      // Exposer la première carte du paquet
      empiler(exposees, sommet(paquet));
      depiler(paquet);

      // Initialisation est finie
      reinitilisation = false;
    }

    Joueur &joueur_courant = joueurs[joueur_id];

    if (joueur_courant.est_perdant) {
      // Ce joueur joue plus
      continue;
    }

    std::printf("* Joueur %d (%c) ", joueur_id + 1, sommet(exposees).lettre);

    afficher_cartes(joueur_courant);
    std::cout << std::endl;

    afficher_mots(mots);

    // Saisie d'une commande
    std::cout << "> ";

    char commande;
    std::cin >> commande;

    bool commande_valide; // Si la saisie est valide

    // Executer la commande
    switch (commande) {
    case 'T':
      // Talon
      commande_valide = piocher(paquet, joueur_courant, exposees);
      break;
    case 'E':
      // Exposées
      commande_valide = piocher(exposees, joueur_courant, exposees);
      break;
    case 'P':
      commande_valide = poser(joueur_courant, mots);
      break;
    case 'R':
      commande_valide = remplacer(joueur_courant, mots);
      break;
    case 'C':
      commande_valide = completer(joueur_courant, mots);
      break;
    default:
      commande_valide = false;
    }

    if (!commande_valide) {
      std::cout << "Commande invalide... Recommencez" << std::endl;
      continue;
    }

    if (joueur_courant.main.restantes == 0) {
      // Le tour est fini
      // On calcule les points
      reinitilisation = true;

      for (unsigned int i = 0; i < (unsigned int)nombre_joueurs; i++) {
        Joueur &joueur = joueurs[i];
        joueur.score += calculer_score(joueur);

        if (joueur.score >= 100) {
          std::cout << "Le joueur " << i + 1 << " a perdu !" << std::endl;
          joueur.est_perdant = true;
          nombre_joueurs_actifs--;
        }
      }
    }

    if (reinitilisation) {
      detruire(mots);
      detruire(paquet);
      detruire(exposees);

      for (unsigned int i = 0; (int)i < nombre_joueurs; i++)
        detruire(joueurs[i].main.cartes);
    }
  }

  unsigned int gagnant_id = 0; // ID du joueur gagnant

  if (nombre_joueurs_actifs == 1) {
    // Il ne reste qu'un seul joueur non perdant
    // Il est donc le gagnant

    for (unsigned int i = 0; i < (unsigned int)nombre_joueurs; i++) {
      Joueur &joueur = joueurs[i];

      if (!joueur.est_perdant) {
        gagnant_id = i;
        break;
      }
    }
  } else if (nombre_joueurs_actifs == 0) {
    // Tous les joueurs ont atteint plus de 100 points
    // Donc il faut retrouver celui ayant le moins de points
    unsigned int score_min = UINT_MAX;

    for (unsigned int i = 0; i < (unsigned int)nombre_joueurs; i++) {
      Joueur &joueur = joueurs[i];

      if (joueur.score < score_min) {
        score_min = joueur.score;
        gagnant_id = i;
      }
    }
  }

  std::cout << "Felicitations au joueur " << gagnant_id + 1 << ", il a gagne!" << std::endl;
}
