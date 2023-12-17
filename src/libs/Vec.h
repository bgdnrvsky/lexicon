#ifndef _CONTENEURTDE_
#define _CONTENEURTDE_

#include "Item.h"

typedef struct {
	unsigned int capacite;
	unsigned int len;
	unsigned int pasExtension;
	Item* tab;
} Vec;

void initialiser(Vec& vec, unsigned int cap);
void detruire(Vec& vec);
Item lire(const Vec& vec, unsigned int pos); 
void ecrire(Vec& vec, unsigned int pos, const Item& it);
void melanger(Item* tab, unsigned int nb);

#endif
