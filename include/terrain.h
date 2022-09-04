/* Auteur : Césaire Agonsè
 * Création: 04-11-21
 * Modification: 05-01-22 */

#ifndef __TERRAIN__
#define __TERRAIN__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define HAUTEUR 43
#define LARGEUR 63

#define NB_MONSTRE 10

/*
#define HAUTEUR 10
#define LARGEUR 12
*/

#include "../include/item.h"
#include "../include/monstre.h"
#include "../include/direction.h"

typedef enum celltype{
    WALL,
    ROOM,
    MONSTER,
    TREASURE,
    STAIR_UP,
    STAIR_DOWN
} Celltype;

typedef union surCase{
    struct monstre *monster;
    struct tresor *tresor;
} surCase;

typedef struct cell{
    Celltype type;
    int x; /*abscisse*/
    int y; /*ordonnnée*/
    union surCase surCase;
    
} Cell;

typedef struct listeCell{
    struct cell *case_;
    struct listeCell *suivante;
} ListeCell;

/*plateau de jeu qui sera un etage*/
typedef struct plateau {
    Cell **grille;
    int niveau;
}Plateau;

/*Fonction qui initialise un étage avec tout wall*/
int initialiseEtage(Plateau *plateau, int niveau);

/*Calcule la distance de manathan entre 2 case1(x1,y1)
* et case2(x2,y2)*/
/*pas encore utile*/
int distanceManathan(Cell case1, Cell case2);

/*Retourne la valeur absolue d'un nombre*/
int valeurAbsolue(int nb);

/*Génère un labyrinthe à partir de la case escalier aux
* coordonées (x,y) de case_*/
int generationLabyrinthe(Plateau *plateau, Cell case_);

/*Retourne 1 si les coordonées (x,y) de case_ est dite
* admissble, 0 sinon*/
int caseEstAdmissible(Plateau *plateau, Cell *case_);

/*Alloue et renvoie un struct ListeCell avec case_ et
NULL en suivant
case peut être NULL en parametre*/
ListeCell* alloue_cellule(Cell *case_);

/*Ajoute la case case_ en fin de liste liste, Renvoie
* 1 si succès 0 sinon,
* renvoie 0 si la case est null
* renvoie 0 si la case est deja dans la liste*/
int ajouterCase(ListeCell *liste, Cell *case_);

/*Renvoie l'adresse de la dernière case de la liste*/
ListeCell* derniere_case(ListeCell *liste);

/*Renvoie l'adresse de la numeme case de la liste*/
Cell* trouverCaseNum(ListeCell *liste, int num);

/*Enleve la case case_ à la liste de case liste, retourne
* 1 si succès 0 sinon*/
int supprimeCaseListe(ListeCell *liste, Cell *case_);

/*Il manque la fonction vider liste*/
void viderListe(ListeCell *liste);

/*Affiche toutes les cases de la liste, Renvoie 1 si
*tout se passe bien, 0 si la liste est vide ou null*/
int afficheListe(ListeCell *liste);

/*Affiche la case, Renvoie 1 si tout se passe bien
* 0 si la case est null*/
int afficheCase(Cell *case_);

/*Renvoie une case adjacente du plateau dans la direction direction,
* si jamais c'est un bord ou la direction n'est pas entre 0 et 3 
* la fonction renvoie NULL 
* le paramtre wall (1 ou 0) permet de prendre en compte les murs ou non*/
Cell* caseAdjacente(Plateau *plateau, Cell *case_, Direction direction, int wall);

/*Compte le nombre de case de type type dans la liste liste*/
int nombreDeCaseListeType(ListeCell *liste, int type);

/*Compte le nombre de case dans la liste liste*/
int nombreDeCaseListe(ListeCell *liste);

/*affiche en ascii brute le plateau (pour le debug)*/
/*affiche pas très bien mais la juste par principe*/
void affichePlateau(Plateau *p);

/*Fonction qui Génère un étage tout entier labyrinthe, montre
trésor et escalier*/
Plateau* generationEtage(int niveau);

/*Fonction qui rajoute nbEtages au tableau de plateau
* Renvoie 1 si tout se passe bien, 0 sinon*/
int rajouteEtage(Plateau **plateau, int nbEtageMax);
/*FONCTION PAS TOTALEMENT SAFE NIVEAU MEMOIRE*/

#endif