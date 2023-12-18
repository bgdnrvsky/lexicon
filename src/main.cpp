#include "Main.h"
#include "Joueur.h"
#include "Paquet.h"
#include "libs/Pile.h"
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

  for (unsigned int i = 0; i < (unsigned int)nombre_joueurs; i++)
    joueurs[i] = (Joueur){
        .id = i + 1, .score = 0, .main = (Main){.cartes = {}, .restantes = 0}};

  Paquet paquet;

  initialiser(paquet, CARTES_PAR_PAQUET);
  remplir(paquet);

  melanger(paquet.tab, CARTES_PAR_PAQUET);

  // Distribuer les cartes aux joueurs
  for (unsigned int i = 0; i < (unsigned int)nombre_joueurs; i++) {
      distribuer(paquet, joueurs[i]);
  }

  for (unsigned int i = 0; i < (unsigned int)nombre_joueurs; i++) {
    Joueur joueur = joueurs[i];
    std::cout << "Joueur " << joueur.id << " : " << joueur.score << " points"
              << " : " << joueur.main.restantes << " cartes restantes"
              << std::endl;

    std::cout << "Cartes : " << std::endl;
    for (unsigned int j = 0; j < joueur.main.restantes; j++) {
      std::cout << "\t"
                << "'" << joueur.main.cartes[j].lettre << "'"
                << " qui vaut " << joueur.main.cartes[j].valeur << std::endl;
    }
  }

  detruire(paquet);
  return 0;
}
