#include "Vec.h"
#include "Item.h"
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <ctime>
using namespace std;

void initialiser(Vec &c, unsigned int capa) {
  assert((capa > 0));
  c.capacite = capa;
  c.len = 0;
  c.pasExtension = 2;
  // arr�t du programme en cas d'erreur d'allocation
  c.tab = new Item[capa];
}

void detruire(Vec &c) {
  delete[] c.tab;
  c.tab = NULL;
}

Item lire(const Vec &c, unsigned int i) {
  assert(i < c.len);
  return c.tab[i];
}

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

void melanger(Item *vec, unsigned int nb) {
  srand(time(NULL));

  for (unsigned int i = nb; i >= 2; --i) {
    unsigned int j = rand() % i;
    Item temp = vec[i - 1];
    vec[i - 1] = vec[j];
    vec[j] = temp;
  }
}
