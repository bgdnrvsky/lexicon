#include "Hand.h"
#include "Paquet.h"
#include "libs/Chaine.h"

void ajouter_carte(Main &main, Carte carte) {
  inserer(main.cartes, carte);
  suivant(main.cartes);
  main.restantes++;
}

void retirer_carte(Main &main) {
  supprimer(main.cartes);
  main.restantes--;
}

bool retrouver_carte(Main &main, Carte carte) {
    for (debut(main.cartes); !estFin(main.cartes); suivant(main.cartes)) {
        if (lire(main.cartes).lettre == carte.lettre) {
            return true;
        }
    }

    return false;
}

bool retrouver_carte_par_lettre(Main &main, char lettre, Carte &carte) {
    for (debut(main.cartes); !estFin(main.cartes); suivant(main.cartes)) {
        if (lire(main.cartes).lettre == lettre) {
            carte.lettre = lettre;
            carte.valeur = TOUTES_CARTES[lettre - 'A'][1];
            return true;
        }
    }

    return false;
}
