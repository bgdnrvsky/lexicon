#include "Commandes.h"
#include "libs/Chaine.h"
#include "libs/Pile.h"
#include <iostream>

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
