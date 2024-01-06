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

/**
 * @brief Initialise un dictionnaire
 * @param[in,out] dictionnaire: le dictionnaire à initialiser
 * @param[in] chemin: le chemin vers le fichier contenant les mots
 */
bool initialiser(Dictionnaire &dictionnaire, const char chemin[]);

/**
 * @brief Recherche un mot dans le dictionnaire
 * @param[in] dictionnaire: le dictionnaire à utiliser
 * @param[in] mot: le mot à rechercher
 * @return true si le mot est présent dans le dictionnaire, false sinon
 */
bool rechercher(const Dictionnaire &dictionnaire, const char mot[]);

#endif
