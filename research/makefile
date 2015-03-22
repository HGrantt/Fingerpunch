#Kompilatorn som används:
CC=g++
#flaggor till kompilatorn:
CFLAGS=-std=c++11

all: menu

menu:
	$(CC) $(CFLAGS) basics.cc menu.cc -lSDL2 -lSDL2_image -lSDL2_mixer -o menu

clean:
	rm -rf *.o menu
run:	
	./menu
