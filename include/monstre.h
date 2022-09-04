/* Auteur : Césaire Agonsè
 * Création: 10-11-21
 * Modification: 10-11-21 */

#ifndef __MONSTRE__
#define __MONSTRE__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "../include/direction.h"

typedef struct monstre{
    int hp;
    int atk;
    int crit;
    int lvl;
    Direction direction;

} Monstre;

/*Renvoie un monstre avec les valeurs de bases
* ou null si echec de malloc*/
Monstre* initialiseMonstre(int niveau);

/*Affiche les attributs du monstre dans le terminal pour le debug */
void afficheMonstre(Monstre *monstre);

/*Renvoie un int de l'attaque effectué par le monstre*/
int attaqueMonstre(Monstre *monstre);
#endif