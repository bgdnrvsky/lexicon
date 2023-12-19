/**
 * @file Pile.cpp
 * Projet sem04-cours-Cpp2
 * @author l'équipe pédagogique
 * @version 1 - 29/11/2014
 * @brief Composant de pile à capacité paramétrée
 * Structures de données et algorithmes - DUT1 Paris Descartes
 */

#include <cassert>
#include <cstddef>
#include <cstring>

#include "Pile.h"

/**
 * @brief Initialiser une pile vide
 * la pile est allouée en mémoire dynamique
 * @see detruire, pour une désallocation en fin d’utilisation
 * @param[out] p : la pile à initialiser
 * @param[in] c : capacité de la pile (nb maximum d‘items stockés)
 * @pre c>0
 */
void initialiser(Pile &p, unsigned int c) {
  assert(c > 0);
  p.capacite = c;
  p.pasExtension = 2;
  p.tab = new Item[c];
  p.sommet = -1;
}

/**
 * @brief Désallouer une pile
 * @see initialiser, la pile a déjà été initialisée
 * @param[in,out] p : la pile à désallouer
 */
void detruire(Pile &p) {
  delete[] p.tab;
  p.tab = NULL;
}

/**
 * @brief Test de pile pleine
 * @param[in] p : la pile testée
 * @return true si p est pleine, false sinon
 */
bool estPleine(const Pile &p) { return (p.sommet == (int)(p.capacite - 1)); }

/**
 * @brief Test de pile vide
 * @param[in] p : la pile testée
 * @return true si p est vide, false sinon
 */
bool estVide(const Pile &p) { return (p.sommet == -1); }

/**
 * @brief Lire l'item au sommet de pile
 * @param[in] p : la pile
 * @return la valeur de l'item au sommet de pile
 * @pre la pile n’est pas vide
 */
Item sommet(const Pile &p) {
  assert(!estVide(p));
  return p.tab[p.sommet];
}

/**
 * @brief Empiler un item sur une pile
 * @param[in,out] p : la pile
 * @param[in] it : l'item à empiler
 * @pre la pile n’est pas pleine
 */
void empiler(Pile &p, Item it) {
  if (p.sommet + 1 >= (int)p.capacite) {
    unsigned int newTaille = (p.sommet + 1) * p.pasExtension;
    Item *newT = new Item[newTaille];

    memcpy(newT, p.tab, sizeof(Item) * newTaille);

    delete[] p.tab;
    p.tab = newT;
    p.capacite = newTaille;
  }
  p.tab[++p.sommet] = it;
}

/**
 * @brief Dépiler l’item au sommet de pile
 * @param[in,out] p : la pile
 * @pre la pile n’est pas vide
 */
void depiler(Pile &p) {
  assert(!estVide(p));
  p.sommet--;
}
