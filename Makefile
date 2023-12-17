MAIN = src/main.cpp
OUT = lexicon
LIBS = src/libs/Vec.cpp src/libs/Pile.cpp src/Paquet.cpp src/Main.cpp
FLAGS = -Wall -Wextra --std=c++20

lexicon:
	g++ -ggdb $(FLAGS) $(MAIN) $(LIBS) -o $(OUT)
