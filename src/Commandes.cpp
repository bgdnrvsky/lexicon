#include "Commandes.h"
#include "Carte.h"
#include "Hand.h"
#include "Mots.h"
#include "Occurrence.h"
#include "Paquet.h"
#include "libs/Chaine.h"
#include "libs/Pile.h"
#include <cassert>
#include <cstring>
#include <iostream>

bool poser_le_mot(Main &main_de_joueur, const char mot[], Mots &mots) {
  if (main_de_joueur.restantes < strlen(mot))
    return false;

  Occurrences counter_joueur;
  initialiser(counter_joueur);
  compter(counter_joueur, main_de_joueur);

  Occurrences counter_mot;
  initialiser(counter_mot);
  compter(counter_mot, *mot);

  Mot nouveau_mot;
  initialiser(nouveau_mot);

  for (unsigned int i = 0; i < strlen(mot); i++) {
    char lettre = mot[i];
    unsigned occurrences_dans_mot = nombre_occurrences(counter_mot, lettre);
    unsigned occurrences_chez_joueur =
        nombre_occurrences(counter_joueur, lettre);

    if (occurrences_dans_mot > occurrences_chez_joueur) {
      // Le nombre de cartes qui contient la lettre n'est pas suffisant
      detruire(nouveau_mot);
      return false;
    }

    Carte carte;
    // On sait deja que la carte est presente dans la main de joueur
    assert(retrouver_carte_par_lettre(main_de_joueur, lettre, carte));

    inserer(nouveau_mot, carte);
    suivant(nouveau_mot);

    retirer_carte(main_de_joueur);

    retirer_occurrence(counter_joueur, carte.lettre);
    retirer_occurrence(counter_mot, carte.lettre);
  }

  ajouter_mot(mots, nouveau_mot);

  detruire(nouveau_mot);

  return true;
}

void poser(Joueur &joueur, Mots &mots) {
  char *mot = new char[NOMBRE_LETTRES];
  std::scanf("%s", mot);

  // TODO: Vérifier que le mot est dans le dictionnaire

  // TODO: Extraire la fonction poser_le_mot a la fonction poser
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
