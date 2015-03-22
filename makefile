#Kompilatorn som används:
CC=g++
#flaggor till kompilatorn
GCCFLAGS=-Wall -Wextra -Weffc++ -Wold-style-cast -Woverloaded-virtual -std=c++11 -pedantic -Werror -Wno-unused-variable -Wno-unused-parameter
GCC_NOFLAGS=-std=c++11
SDL2=-lSDL2 -lSDL2_image -lSDL2_mixer

all: game

game:
	$(CC) $(GCC_NOFLAGS) $(shell find fingerpunch/fingerpunch/src -type f -name *.cpp) $(SDL2) -o game.out

clean:
	rm -rf *.o *.out
run:	
	./game.out
