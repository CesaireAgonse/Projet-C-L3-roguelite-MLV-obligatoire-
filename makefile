# Makefile Projet Donjon Rogue
# $@ nom de la cible
# $< première dependence de la cible
# $? dépendances plus récente que la cible (modifié)
# $^ toutes les dépendances
# $* comme le * dans le shell

CC = gcc
CFLAGS = -ansi -pedantic -Wall -std=c99 -lm
LFLAGS = -lMLV

SRC = src/
BIN = bin/
INC = include/

SOURCE = $(wildcard src/*.c) 
#OBJ = $(patsubst src/%.c,bin/%.o, $(SOURCE))
OBJ = bin/action.o bin/fichier.o bin/graphique.o bin/inventaire.o bin/item.o bin/main.o bin/monstre.o bin/perso.o bin/position.o bin/terrain.o
EXEC = Donjon

$(EXEC) : $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(CFLAGS) $(LFLAGS)

$(BIN)graphique.o : $(SRC)graphique.c
	$(CC) -c $< -o $@ $(CFLAGS) $(LFLAGS)

$(BIN)%.o : $(SRC)%.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean: 
	rm -f $(BIN)*.o

clear:
	rm -f $(EXEC)
