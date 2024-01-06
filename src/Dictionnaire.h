#ifndef _DICTIONNAIRE_H_
#define _DICTIONNAIRE_H_
#include <fstream>

/**
 * @brief Type dictionnaire utilisé pour la recherche de mots
 */
typedef struct {
  const char *chemin;    ///< Le chemin vers le fichier
  std::ifstream fichier; ///< Le fichier lui-même
} Dictionnaire;

bool initialiser(Dictionnaire &dictionnaire, const char chemin[]);
bool rechercher(Dictionnaire &dictionnaire, const char mot[]);

#endif
