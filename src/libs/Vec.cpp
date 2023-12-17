/**
 * @file Vec.cpp
 * Projet sem04-tp-Cpp1-3
 * @author l'�quipe p�dagogique
 * @version 2 - 29/11/2014
 * @brief corrige du TD n�3 sur machine - Exercice 2
 * Structures de donn�es et algorithmes - DUT1 Paris Descartes
 */

#include "Vec.h"
#include "Item.h"
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <ctime>
using namespace std;

/**
 * @brief Initialise un conteneur d'items
 * Allocation en m�moire dynamique du conteneur d'items
 * de capacit� (capa) extensible par pas d'extension (p)
 * @see detruire, pour sa d�sallocation en fin d'utilisation
 * @param[out] c : le conteneur d'items
 * @param [in] capa : capacit� du conteneur
 * @param [in] p : pas d'extension de capacit�
 * @pre capa>0 et p>0
 */
void initialiser(Vec &c, unsigned int capa) {
  assert((capa > 0));
  c.capacite = capa;
  c.len = 0;
  c.pasExtension = 2;
  // arr�t du programme en cas d'erreur d'allocation
  c.tab = new Item[capa];
}

/**
 * @brief D�salloue un conteneur d'items en m�moire dynamique
 * @see initialiser, le conteneur d'items a d�j� �t� allou�
 * @param[out] c : le conteneur d'items
 */
void detruire(Vec &c) {
  delete[] c.tab;
  c.tab = NULL;
}

/**
 * @brief Lecture d'un item d'un conteneur d'items
 * @param[in] c : le conteneur d'items
 * @param[in] i : la position de l'item dans le conteneur
 * @return l'item � la position i
 * @pre i < c.capacite
 */
Item lire(const Vec &c, unsigned int i) {
  assert(i < c.len);
  return c.tab[i];
}

/**
 * @brief Ecrire un item dans un conteneur d'items
 * @param[in,out] c : le conteneur d'items
 * @param[in] i : la position o� ajouter/modifier l'item
 * @param[in] it : l'item � �crire
 */
void ecrire(Vec &c, unsigned int i, const Item &it) {
  if (i >= c.capacite) {
    /* Strat�gie de r�allocation proportionnelle au pas d'extension :
     * initialisez la nouvelle taille du conteneur (newTaille)
     * � i * c.pasExtension */
    unsigned int newTaille = (i + 1) * c.pasExtension;
    /* Allouez en m�moire dynamique un nouveau tableau (newT)
     * � cette nouvelle taille*/
    Item *newT = new Item[newTaille];
    /* Recopiez les items d�j� stock�s dans le conteneur */
    for (unsigned int i = 0; i < c.capacite; ++i)
      newT[i] = c.tab[i];
    /* D�sallouez l'ancien tableau support du conteneur */
    delete[] c.tab;
    /* Actualiser la mise � jour du conteneur en m�moire dynamique
     * Faites pointer le tableau support du conteneur
     * sur le nouveau tableau en m�moire dynamique */
    c.tab = newT;
    /* Actualisez la taille du conteneur */
    c.capacite = newTaille;
  }
  /* Ecriture de l'item (it) � la position i dans le conteneur */
  c.tab[i] = it;
  c.len++;
}

/**
 * @brief Melanger le contenu de liste
 * @param[in,out] c : le conteneur d'items
 */
void melanger(Item *vec, unsigned int nb) {
  srand(time(NULL));

  for (unsigned int i = nb; i >= 2; --i) {
    unsigned int j = rand() % i;
    Item temp = vec[i - 1];
    vec[i - 1] = vec[j];
    vec[j] = temp;
  }
}
