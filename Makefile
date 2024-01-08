MAIN = src/main.cpp
OUT = lexicon
LIBS = src/libs/Vec.cpp src/libs/Pile.cpp src/libs/Chaine.cpp src/Paquet.cpp
FILES = src/Hand.cpp src/Commandes.cpp src/Mots.cpp src/Occurrence.cpp src/Carte.cpp src/Joueur.cpp src/Dictionnaire.cpp
FLAGS = -Wall -Wextra --std=c++20

CC = g++

build:
	$(CC) -ggdb $(FLAGS) $(MAIN) $(LIBS) $(FILES) -o $(OUT)

doc:
	doxygen Doxyfile

test: build_tests
	echo "Lancement des tests"
	./tests/bins/test_initialisiation_dictionnaire
	./tests/bins/recherche_dictionnaire

build_tests: clean prepare_tests objects
	$(CC) tests/test.cpp tests/initialisiation_dictionnaire.cpp tests/objects/*.o -o tests/bins/test_initialisiation_dictionnaire
	$(CC) tests/test.cpp tests/recherche_dictionnaire.cpp tests/objects/*.o -o tests/bins/recherche_dictionnaire

prepare_tests:
	mkdir tests/objects
	mkdir tests/bins
	touch tests/test_dict.txt
	echo "bonjour" >> tests/test_dict.txt
	echo "bonsoir" >> tests/test_dict.txt

objects:
	$(CC) -c $(FILES) $(LIBS)
	mv *.o tests/objects/

clean:
	rm -rf tests/objects
	rm -rf tests/bins
	rm -f tests/test_dict.txt
	rm -f lexicon
