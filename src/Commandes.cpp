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
  compter(counter_mot, mot);

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

bool poser(Joueur &joueur, Mots &mots) {
  char *mot = new char[NOMBRE_LETTRES];
  std::scanf("%s", mot);

  // TODO: Vérifier que le mot est dans le dictionnaire

  // TODO: Extraire la fonction poser_le_mot a la fonction poser
  if (!poser_le_mot(joueur.main, mot, mots)) {
    std::cout
        << "Le mot peut pas etre construit a partir de cartes que vous avez"
        << std::endl;
    return false;
  }

  delete[] mot;
  return true;
}


/**
 * @brief Permet à un joueur piocher une carte du paquet et met une de ses cartes sur le
 * paquet de cartes exposees
 * @param[in,out]: paquet: paquet de cartes a piocher
 * @param[in,out]: joueur: joueur qui pioche
 * @param[in,out]: exposees: paquet de cartes exposées
 * @see debut, estFin, suivant, lire, sommet, depiler, supprimer, empiler et inserer
 */
bool piocher(Paquet &paquet, Joueur &joueur, Paquet &exposees) {
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
    return false;
  }

  Carte carte_prise = sommet(paquet);
  depiler(paquet);

  Carte carte_de_joueur = lire(joueur.main.cartes);
  supprimer(joueur.main.cartes);

  empiler(exposees, carte_de_joueur);
  inserer(joueur.main.cartes, carte_prise);
  debut(joueur.main.cartes);

  return true;
}

/**
 * @brief Remplace un mot pose par un nouveau mot construit a partir de celui-ci en y
 *        inserant des lettres par d'autres lettre detenues par le joueur
 * @param[in,out] joueur: le joueur qui effectue le remplacement
 * @param[in,out] mots: la chaine de mots poses ou se trouve le mot a remplacer
 */
bool remplacer(Joueur &joueur, Mots &mots) {
  unsigned int mot_pos;
  std::cin >> mot_pos;

  char *nouveau_mot = new char[NOMBRE_LETTRES];
  std::scanf("%s", nouveau_mot);

  if (mot_pos > nombre_mots(mots)) {
    std::cout << "Le mot n'existe pas" << std::endl;
    delete[] nouveau_mot;
    return false;
  }

  for (debut(mots); mot_pos > 1; suivant_mot(mots))
    mot_pos--;

  Mot mot;
  lire_mot(mots, mot);
  debut(mot);

  if (strlen(nouveau_mot) != taille_mot(mot)) {
    std::cout << "Le nouveau mot peut pas remplacer l'ancien car le nombre de "
                 "lettres est different"
              << std::endl;
    delete[] nouveau_mot;
    return false;
  }

  Occurrences compter_joueur;
  initialiser(compter_joueur);
  compter(compter_joueur, joueur.main);

  for (unsigned int i = 0; i < strlen(nouveau_mot); i++) {
    Carte lettre_origin = lire(mot);
    char nouvelle_lettre = nouveau_mot[i];

    if (nouvelle_lettre != lettre_origin.lettre) {
      // La lettre doit etre remplacee par une carte de la main de joueur
      if (nombre_occurrences(compter_joueur, nouvelle_lettre) == 0) {
        // On peut pas remplacer la lettre
        std::cout << "Le nouveau mot ne peut pas etre construit a partir de "
                     "cartes possedees par joueur"
                  << std::endl;
        delete[] nouveau_mot;
        return false;
      }

      Carte nouvelle_carte;
      assert(retrouver_carte_par_lettre(
          joueur.main, nouvelle_lettre,
          nouvelle_carte)); // On sait que la carte est presente

      retirer_carte(joueur.main);
      retirer_occurrence(compter_joueur, nouvelle_lettre);

      ecrire(mot, nouvelle_carte);
    }

    suivant(mot);
  }

  delete[] nouveau_mot;
  return true;
}

/**
 * @brief Complète un mot pose par un nouveau mot construit a partir de celui-ci en y
 *        inserant des lettres detenues par le joueur.
 * @param[in,out] joueur : le joueur qui complete le mot
 * @param[in,out] mots: la chaine de mots poses ou se trouve le mot a completer
 */
bool completer(Joueur &joueur, Mots &mots) {
  unsigned int mot_pos;
  std::cin >> mot_pos;

  char *nouveau_mot = new char[NOMBRE_LETTRES];
  std::scanf("%s", nouveau_mot);

  if (mot_pos > nombre_mots(mots)) {
    std::cout << "Le mot n'existe pas" << std::endl;
    delete[] nouveau_mot;
    return false;
  }

  for (debut(mots); mot_pos > 1; suivant_mot(mots))
    mot_pos--;

  Mot mot;
  lire_mot(mots, mot);
  debut(mot);

  if (strlen(nouveau_mot) <= taille_mot(mot)) {
    std::cout << "Le nouveau mot doit avoir plus de lettres que l'ancien"
              << std::endl;
    delete[] nouveau_mot;
    return false;
  }

  // Verifier que le nouveau mot preserve l'ordre des lettres de l'ancien
  unsigned int bordure_gauche =
      0; // La position a partir de laquelle on va chercher
  for (debut(mot); lire(mot).lettre != '\0'; suivant(mot)) {
    Carte carte = lire(mot);
    bool carte_trouvee = false;

    for (unsigned int i = bordure_gauche; i < strlen(nouveau_mot); i++) {
      if (nouveau_mot[i] == carte.lettre) {
        // On a trouve la lettre
        bordure_gauche = i + 1;
        carte_trouvee = true;
        break;
      }
    }

    if (!carte_trouvee) {
      std::cout << "Le nouveau mot doit preserver l'ordre des lettres de "
                   "l'ancien"
                << std::endl;
      delete[] nouveau_mot;
      return false;
    }
  }

  // Verifier que le nouveau mot peut etre construit a partir de la main de
  // joueur et du mot deja present
  Occurrences compteur_joueur;
  initialiser(compteur_joueur);
  compter(compteur_joueur, joueur.main);

  Occurrences compteur_mot;
  initialiser(compteur_mot);
  compter(compteur_mot, mot);

  for (unsigned int i = 0; i < strlen(nouveau_mot); i++) {
    char lettre = nouveau_mot[i];

    if (nombre_occurrences(compteur_mot, lettre) > 0) {
      retirer_occurrence(compteur_mot, lettre);
      continue;
    }

    if (nombre_occurrences(compteur_joueur, lettre) > 0) {
      retirer_occurrence(compteur_joueur, lettre);
      continue;
    }

    // La lettre n'a pu etre contruite ni de la main de joueur ni de lettres du
    // mot deja present
    std::cout << "Le mot peut pas etre consturuit" << std::endl;
    delete[] nouveau_mot;
    return false;
  }

  Main nouvelle_main;
  initialiser(nouvelle_main);

  for (char i = 'A'; i < NOMBRE_LETTRES + 'A'; i++) {
    unsigned occurrences = nombre_occurrences(
        compteur_joueur,
        i); // Combien de fois cette lettre sera presente dans la nouvelle main

    for (unsigned j = 0; j < occurrences; j++)
      ajouter_carte(nouvelle_main, nouvelle_carte(i));
  }

  detruire(joueur.main);
  joueur.main = nouvelle_main;

  // Modifier le mot dans la liste de mots

  // On supprime le mot original
  while (lire(mots).lettre != '\0')
    supprimer(mots);

  // On insere le nouveau mot
  for (unsigned int i = 0; i < strlen(nouveau_mot); i++) {
    inserer(mots, nouvelle_carte(nouveau_mot[i]));
    suivant(mots);
  }

  delete[] nouveau_mot;
  return true;
}
