CC=gcc
CFLAGS=-W -Wall -ansi -pedantic -std=c99
LDFLAGS= -lSDL -lSDL_ttf -lSDL_mixer
EXEC=taquin
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

taquin: $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

main.o: fonction_importante.h
main.o: affichage.h
main.o: jeu.h
fonction_importante.o: mouvement.h
jeu.o: mouvement.h
jeu.o: fonction_importante.h

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC) 
