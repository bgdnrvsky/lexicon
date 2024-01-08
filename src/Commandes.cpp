#include "Commandes.h"
#include "Carte.h"
#include "Dictionnaire.h"
#include "Hand.h"
#include "Mots.h"
#include "Occurrence.h"
#include "Paquet.h"
#include "libs/Chaine.h"
#include "libs/Pile.h"
#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>

Status poser(std::istringstream &is, Joueur &joueur, Mots &mots,
             const Dictionnaire &dictionnaire) {
  char mot[NOMBRE_LETTRES];

  if (!(is >> mot))
    return COMMANDE_INVALIDE;

  is >> std::ws;
  if (!is.eof())
    // Il reste encore des caracteres dans la commande
    return COMMANDE_INVALIDE;

  if (!rechercher(dictionnaire, mot))
    return MOT_INEXISTANT;

  if (joueur.main.restantes < strlen(mot))
    return COMMANDE_INVALIDE;

  Occurrences counter_joueur;
  initialiser(counter_joueur);
  compter(counter_joueur, joueur.main);

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
      return COMMANDE_INVALIDE;
    }

    Carte carte;
    // On sait deja que la carte est presente dans la main de joueur
    assert(retrouver_carte_par_lettre(joueur.main, lettre, carte));

    inserer(nouveau_mot, carte);
    suivant(nouveau_mot);

    retirer_carte(joueur.main);

    retirer_occurrence(counter_joueur, carte.lettre);
    retirer_occurrence(counter_mot, carte.lettre);
  }

  ajouter_mot(mots, nouveau_mot);

  detruire(nouveau_mot);

  return SUCCES;
}

Status piocher(std::istringstream &is, Paquet &paquet, Joueur &joueur,
               Paquet &exposees) {
  char lettre;
  if (!(is >> lettre))
    return COMMANDE_INVALIDE;

  is >> std::ws;
  if (!is.eof())
    // Il reste encore des caracteres dans la commande
    return COMMANDE_INVALIDE;

  // Vérifier que la carte est dans la main du joueur
  bool carte_trouvee = false;

  for (debut(joueur.main.cartes); !estFin(joueur.main.cartes);
       suivant(joueur.main.cartes)) {
    if (lire(joueur.main.cartes).lettre == lettre) {
      carte_trouvee = true;
      break;
    }
  }

  if (!carte_trouvee)
    return COMMANDE_INVALIDE;

  Carte carte_prise = sommet(paquet);
  depiler(paquet);

  Carte carte_de_joueur = lire(joueur.main.cartes);
  supprimer(joueur.main.cartes);

  empiler(exposees, carte_de_joueur);
  inserer(joueur.main.cartes, carte_prise);
  debut(joueur.main.cartes);

  return SUCCES;
}

Status remplacer(std::istringstream &is, Joueur &joueur, Mots &mots,
                 const Dictionnaire &dictionnaire) {
  unsigned int mot_pos;
  if (!(is >> mot_pos))
    return COMMANDE_INVALIDE;

  char nouveau_mot[NOMBRE_LETTRES];
  if (!(is >> nouveau_mot))
    return COMMANDE_INVALIDE;

  is >> std::ws;
  if (!is.eof())
    // Il reste encore des caracteres dans la commande
    return COMMANDE_INVALIDE;

  if (!rechercher(dictionnaire, nouveau_mot))
    return MOT_INEXISTANT;

  if (mot_pos > nombre_mots(mots))
    return COMMANDE_INVALIDE;

  // Se deplacer vers le mot qu'on veut
  for (debut(mots); mot_pos > 1; suivant_mot(mots))
    mot_pos--;

  Mot mot;
  lire_mot(mots, mot);
  debut(mot);

  if (strlen(nouveau_mot) != taille_mot(mot))
    return COMMANDE_INVALIDE;

  Occurrences compter_joueur;
  initialiser(compter_joueur);
  compter(compter_joueur, joueur.main);

  for (unsigned int i = 0; i < strlen(nouveau_mot); i++) {
    Carte lettre_origin = lire(mot);
    char nouvelle_lettre = nouveau_mot[i];

    if (nouvelle_lettre != lettre_origin.lettre) {
      // La lettre doit etre remplacee par une carte de la main de joueur
      if (nombre_occurrences(compter_joueur, nouvelle_lettre) == 0)
        // On peut pas remplacer la lettre
        return COMMANDE_INVALIDE;

      Carte carte_de_joueur;
      assert(retrouver_carte_par_lettre(
          joueur.main, nouvelle_lettre,
          carte_de_joueur)); // On sait que la carte est presente

      ecrire(joueur.main.cartes, nouvelle_carte(lettre_origin.lettre));
      retirer_occurrence(compter_joueur, nouvelle_lettre);

      ecrire(mot, carte_de_joueur);
    }

    suivant(mot);
  }

  return SUCCES;
}

Status completer(std::istringstream &is, Joueur &joueur, Mots &mots,
                 const Dictionnaire &dictionnaire) {
  unsigned int mot_pos;
  if (!(is >> mot_pos))
    return COMMANDE_INVALIDE;

  char nouveau_mot[NOMBRE_LETTRES];
  if (!(is >> nouveau_mot))
    return COMMANDE_INVALIDE;

  is >> std::ws;
  if (!is.eof())
    // Il reste encore des caracteres dans la commande
    return COMMANDE_INVALIDE;

  if (!rechercher(dictionnaire, nouveau_mot))
    return MOT_INEXISTANT;

  if (mot_pos > nombre_mots(mots))
    return COMMANDE_INVALIDE;

  // Se deplacer vers le mot qu'on veut
  for (debut(mots); mot_pos > 1; suivant_mot(mots))
    mot_pos--;

  Mot mot;
  lire_mot(mots, mot);
  debut(mot);

  if (strlen(nouveau_mot) <= taille_mot(mot))
    return COMMANDE_INVALIDE;

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

    if (!carte_trouvee)
      return COMMANDE_INVALIDE;
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
    return COMMANDE_INVALIDE;
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

  return SUCCES;
}
