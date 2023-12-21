#ifndef _OCCURRENCE_H_
#define _OCCURRENCE_H_

#include "Paquet.h"

typedef unsigned Occurrences[NOMBRE_LETTRES];

void initialiser(Occurrences &occurrences);
unsigned nombre_occurrences(Occurrences &occurrences, char lettre);
void retirer_occurrence(Occurrences &occurrences, char lettre);
void ajouter_occurrence(Occurrences &occurrences, char lettre);
void compter(Occurrences &occurrences, Main &main);
void compter(Occurrences &occurrences, const char &mot);

#endif
