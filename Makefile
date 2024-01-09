MAIN = src/main.cpp
OUT = lexicon
LIBS = src/libs/Vec.cpp src/libs/Pile.cpp src/libs/Chaine.cpp src/Paquet.cpp
FILES = src/Hand.cpp src/Commandes.cpp src/Mots.cpp src/Occurrence.cpp src/Carte.cpp src/Joueur.cpp src/Dictionnaire.cpp
FLAGS = -Wall -Wextra --std=c++20 -ggdb

CC = g++

build:
	$(CC) $(FLAGS) $(MAIN) $(LIBS) $(FILES) -o $(OUT)

doc:
	doxygen Doxyfile

test: build_tests
	echo "Lancement des tests"
	./tests/bins/test_initialisiation_dictionnaire
	./tests/bins/recherche_dictionnaire
	./tests/bins/manipulation_cartes_main

build_tests: clean prepare_tests objects
	$(CC) $(FLAGS) tests/test.cpp tests/initialisiation_dictionnaire.cpp tests/objects/*.o -o tests/bins/test_initialisiation_dictionnaire
	$(CC) $(FLAGS) tests/test.cpp tests/recherche_dictionnaire.cpp tests/objects/*.o -o tests/bins/recherche_dictionnaire
	$(CC) $(FLAGS) tests/test.cpp tests/manipulation_cartes_main.cpp tests/objects/*.o -o tests/bins/manipulation_cartes_main

prepare_tests:
	mkdir tests/objects
	mkdir tests/bins
	touch tests/test_dict.txt
	echo "bonjour" >> tests/test_dict.txt
	echo "bonsoir" >> tests/test_dict.txt

objects:
	$(CC) $(FLAGS) -c $(FILES) $(LIBS)
	mv *.o tests/objects/

clean:
	rm -rf tests/objects
	rm -rf tests/bins
	rm -f tests/test_dict.txt
	rm -f lexicon
