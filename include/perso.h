/* Auteur : Césaire Agonsè
 * Création: 10-11-21
 * Modification: 10-11-21 */

#ifndef __PERSO__
#define __PERSO__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "../include/item.h"
typedef enum armetype{
    MELEE,
    MAGIC
} Armetype;

typedef struct perso{
    int hp;
    int mp;
    int atk;
    int inte;
    int def;
    int exp;
    int lv;
    int crit;
    int bonusExp;

    struct item *armure;
    struct item *arme;
    struct item *baguette;
    struct item *popo;
    
    Armetype modeAtk;

} Perso;

/*Renvoie un perso avec les valeurs de bases
* ou null si echec de malloc*/
Perso* initialisePerso();

/*Affiche les attributs du perso dans le terminal pour le debug */
void affichePerso(Perso *perso);

/*Verifie si la condition de passage de niveau
* est vrai, Renvoie 1 si au passage de niveau
* 0 sinon */
int niveauSup(Perso *perso);

/*Renvoie un int de l'attaque effectué par le personnage*/
int attaque(Perso *perso);

/*Renvoie un int de l'attaque effectué par le personnage
* et enleve 20 mp au perso
* Si le perso n'a pas assez de mp la fonction renvoie 0*/
int attaqueMagique(Perso *perso);

#endif