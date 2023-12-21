#include "Commandes.h"
#include "Carte.h"
#include "Hand.h"
#include "Paquet.h"
#include "libs/Chaine.h"
#include "libs/Pile.h"
#include <cstring>
#include <iostream>

bool poser_le_mot(Main &main_de_joueur, const char mot[], Chaine &mots) {
  if (main_de_joueur.restantes < strlen(mot))
    return false;

  unsigned short counter_joueur[NOMBRE_LETTRES] = {0};

  for (debut(main_de_joueur.cartes); !estFin(main_de_joueur.cartes);
       suivant(main_de_joueur.cartes))
    counter_joueur[lire(main_de_joueur.cartes).lettre - 'A']++;

  unsigned short counter_mot[NOMBRE_LETTRES] = {0};

  for (unsigned int i = 0; i < strlen(mot); i++)
    counter_mot[mot[i] - 'A']++;

  Chaine nouveau_mot;
  initialiser(nouveau_mot);

  Main nouvelle_main;
  nouvelle_main.restantes = 0;
  initialiser(nouvelle_main.cartes);

  for (debut(main_de_joueur.cartes); !estFin(main_de_joueur.cartes);
       suivant(main_de_joueur.cartes)) {
    Carte carte = lire(main_de_joueur.cartes);

    unsigned short &carte_chez_joueur = counter_joueur[carte.lettre - 'A'];
    unsigned short &carte_dans_mot = counter_mot[carte.lettre - 'A'];

    if (carte_chez_joueur < carte_dans_mot) {
      detruire(nouveau_mot);
      detruire(nouvelle_main.cartes);
      return false;
    }

    if (carte_dans_mot > 0) {
      inserer(nouveau_mot, carte);

      counter_joueur[carte.lettre - 'A']--;
      counter_mot[carte.lettre - 'A']--;
    } else {
      // Cette lettre n'est pas dans le mot
      ajouter_carte(nouvelle_main, carte);
    }
  }

  for (unsigned int i = 0; i < strlen(mot); i++) {
    if (counter_mot[mot[i] - 'A'] > 0) {
      detruire(nouveau_mot);
      detruire(nouvelle_main.cartes);
      return false;
    }
  }

  fin(mots);
  for (debut(nouveau_mot); !estFin(nouveau_mot); suivant(nouveau_mot)) {
    inserer(mots, lire(nouveau_mot));
    suivant(mots);
  }

  inserer(mots, SPACER);
  suivant(mots);

  detruire(nouveau_mot);

  detruire(main_de_joueur.cartes);

  main_de_joueur = nouvelle_main;

  return true;
}

void poser(Joueur &joueur, Chaine &mots) {
  char *mot = new char[NOMBRE_LETTRES];
  std::scanf("%s", mot);

  // TODO: Vérifier que le mot est dans le dictionnaire

  if (!poser_le_mot(joueur.main, mot, mots)) {
    std::cout
        << "Le mot peut pas etre construit a partir de cartes que vous avez"
        << std::endl;
  }

  delete[] mot;
}

/*
 * @brief: Le joueur pioche une carte du paquet et met une de ses cartes sur le
 * paquet de cartes exposéeses
 * @param[IN, OUT]: Paquet d'où le joueur pioche
 * @param[IN, OUT]: Joueur qui pioche
 * @param[IN, OUT]: Paquet de cartes exposées
 */
void piocher(Paquet &paquet, Joueur &joueur, Paquet &exposees) {
  char lettre;
  std::cin >> lettre;

  // Vérifier que la carte est dans la main du joueur
  bool carte_trouvee = false;

  for (debut(joueur.main.cartes); !estFin(joueur.main.cartes);
       suivant(joueur.main.cartes)) {
    if (lire(joueur.main.cartes).lettre == lettre) {
      carte_trouvee = true;
      break;
    }
  }

  if (!carte_trouvee) {
    std::cout << "La carte " << lettre << " n'est pas dans votre main"
              << std::endl;
    return;
  }

  Carte carte_prise = sommet(paquet);
  depiler(paquet);

  Carte carte_de_joueur = lire(joueur.main.cartes);
  supprimer(joueur.main.cartes);

  empiler(exposees, carte_de_joueur);
  inserer(joueur.main.cartes, carte_prise);
  debut(joueur.main.cartes);
}
