#ifndef _TESTS_H_
#define _TESTS_H_

#include <cstring>

const unsigned int TAILLE_MAX = 200;

const char TEXTE_VERT[] = "\x1b[32;49m";
const char TEXTE_ROUGE[] = "\x1b[31;49m";
const char TEXTE_ITALIQUE[] = "\x1b[3m";
const char TEXTE_GRAS[] = "\x1b[1m";
const char TEXTE_RESET[] = "\x1b[39m";

#define REPORT_MESSAGE(message)                                                \
  do {                                                                         \
    strcpy(msg, "En fonction ");                                               \
    strcat(msg, __FILE_NAME__);                                                \
    strcat(msg, "/");                                                          \
    strcat(msg, __FUNCTION__);                                                 \
    strcat(msg, ": ");                                                         \
    strcat(msg, message);                                                      \
    strcat(msg, ". Ce que est inattendu");                                     \
  } while (0)

#define REPORT_FILENAME strcpy(nom_teste, __FILE_NAME__);

#define GENERATE_TEST                                                          \
  bool test(char *nom_teste, char *msg_erreur) {                               \
    REPORT_FILENAME;                                                           \
    return test_valide(msg_erreur) && !test_invalide(msg_erreur);              \
  }

bool test_valide(char *msg);
bool test_invalide(char *msg);
bool test(char *nom_teste, char *msg_erreur);

#endif
