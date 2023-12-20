#ifndef _CARTE_H_
#define _CARTE_H_

typedef struct {
  char lettre;
  unsigned int valeur;
} Carte;

const Carte SPACER = (Carte){
    .lettre = '\0',
    .valeur = 0,
};

#endif
