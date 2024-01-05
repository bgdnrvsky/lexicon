MAIN = src/main.cpp
OUT = lexicon
LIBS = src/libs/Vec.cpp src/libs/Pile.cpp src/libs/Chaine.cpp src/Paquet.cpp
FILES = src/Hand.cpp src/Commandes.cpp src/Mots.cpp src/Occurrence.cpp src/Carte.cpp src/Joueur.cpp src/Dictionnaire.cpp
FLAGS = -Wall -Wextra --std=c++20

lexicon:
	g++ -ggdb $(FLAGS) $(MAIN) $(LIBS) $(FILES) -o $(OUT)
