#include "Commandes.h"
#include "Dictionnaire.h"
#include "Joueur.h"
#include "Mots.h"
#include "Paquet.h"
#include "libs/Vec.h"
#include <climits>
#include <iostream>
#include <sstream>

#define MAX_NOMBRE_JOUEURS 4
#define COMMANDE_LEN_MAX 100

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
    initialiser(joueurs[i], i);

  unsigned int nombre_joueurs_actifs =
      nombre_joueurs; // Nombre de joueurs qui sont toujours en jeu

  bool reinitilisation =
      true; // Lorsque le premier ou nouveau tour on initialise les objets

  Dictionnaire dictionnaire;
  const char chemin_dictionnaire[] = "ods4.txt";

  if (!initialiser(dictionnaire, chemin_dictionnaire)) {
    std::cout << "Impossible d'initialiser le dictionnaire" << std::endl;
    for (unsigned int i = 0; (int)i < nombre_joueurs; i++)
      detruire(joueurs[i].main.cartes);
    return 1;
  }

  Paquet paquet;
  Paquet exposees; // Les cartes exposées
  Mots mots;       // Les mots poses

  unsigned int joueur_id = 0; // ID du joueur qui joue
  unsigned int tour = 0;      // Nombre de tours joues

  while (nombre_joueurs_actifs > 1) {
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
      tour++;
      joueur_id = (joueur_id + 1) % nombre_joueurs;
      continue;
    }

    std::printf("* Joueur %d (%c) ", joueur_id + 1, sommet(exposees).lettre);

    afficher_cartes(joueur_courant);
    std::cout << std::endl;

    afficher_mots(mots);

    // Saisie d'une commande
    std::cout << "> ";

    char commande[COMMANDE_LEN_MAX];

    std::cin.getline(commande, COMMANDE_LEN_MAX);

    std::istringstream is(commande);

    char type_de_commande;
    is >> type_de_commande;

    Status status_commande; // Si la saisie est valide

    // Executer la commande
    switch (type_de_commande) {
    case 'T':
      // Talon
      status_commande = piocher(is, paquet, joueur_courant, exposees);
      break;
    case 'E':
      // Exposées
      status_commande = piocher(is, exposees, joueur_courant, exposees);
      break;
    case 'P':
      status_commande = poser(is, joueur_courant, mots, dictionnaire);
      break;
    case 'R':
      status_commande = remplacer(is, joueur_courant, mots, dictionnaire);
      break;
    case 'C':
      status_commande = completer(is, joueur_courant, mots, dictionnaire);
      break;
    default:
      status_commande = COMMANDE_INVALIDE;
    }

    switch (status_commande) {
    case COMMANDE_INVALIDE:
      std::cout << "Coup invalide, recommencez" << std::endl;
      continue;
      break;
    case MOT_INEXISTANT:
      std::cout << "Mot invalide, vous passez votre tour" << std::endl;
      joueur_courant.score += 3;
      break;
    case SUCCES:
      break;
    }

    if (joueur_courant.main.restantes == 0) {
      // Le tour est fini
      // On calcule les points
      reinitilisation = true;

      std::cout << "Le tour est fini" << std::endl;

      for (unsigned int i = 0; i < (unsigned int)nombre_joueurs; i++) {
        Joueur &joueur = joueurs[i];
        joueur.score += calculer_score(joueur);

        if (joueur.score >= 100) {
          joueur.est_perdant = true;
          joueur.tour_perdu = tour;
          nombre_joueurs_actifs--;
        }
      }

      afficher_scores(joueurs, nombre_joueurs, tour);
    }

    tour++;
    joueur_id = (joueur_id + 1) % nombre_joueurs;

    if (reinitilisation) {
      detruire(mots);
      detruire(paquet);
      detruire(exposees);

      for (unsigned int i = 0; (int)i < nombre_joueurs; i++)
        detruire(joueurs[i].main);
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

  std::cout << "Felicitations au joueur " << gagnant_id + 1 << ", il a gagne!"
            << std::endl;
}
