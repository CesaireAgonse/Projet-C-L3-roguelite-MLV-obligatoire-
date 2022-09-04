/* Auteur : Césaire Agonsè
 * Création: 10-11-21
 * Modification: 05-01-22 */

#ifndef __POSITION__
#define __POSITION__

#include <stdio.h>
#include <stdlib.h>

#include "../include/terrain.h"

typedef struct position{
    int x;
    int y;
    Direction direction; 
    int etage; /*numéro de l'étage courant*/
    int nbEtageMax; /*numéro de l'étage max atteint*/

} Position;

/*Initialise une Position de joueur avec les valeurs de base
* Retourne donc la Position , null si erreur de malloc*/
Position* initialisePosition(int x, int y);

/*Deplace le perso (bah oe lojik)
* joueur est la position du perso
* Retourne 1 si le perso arrive à se deplacer retourne 0 sinon*/
int deplacerJoueur(Plateau plateau, Position *joueur, Direction direction);

#endif