/* Auteur : Césaire Agonsè
 * Création: 21-11-21
 * Modification: 21-11-21 */

#ifndef __INVENTAIRE__
#define __INVENTAIRE__

#include <stdio.h>
#include <stdlib.h>

#include "../include/item.h"

#define NB_ITEM_MAX 12

typedef struct inventaire {
    Item *content[NB_ITEM_MAX];
}Inventaire;

/*Initialise un inventaire avec des objets de type vide
* Retourne donc 1 si succes et 0 si il y a un probleme de malloc */
int initialiseInventaire(Inventaire *invent);

/*Fonction ajoute l'item dans l'inventaire en écrasant un item de type vide,
* retourne 1 si succes, 0 sinon*/
int ajouteItem(Inventaire *invent, Item *item);

/*Renvoie 1 si l'item jeté dans le paradis de la mémoire
* a bien été jeté, 0 si il n'est pas la*/
int jetteItem(Inventaire *invent, Item *item);

/*Regarde si dans l'inventaire il y a n places vides
* retourne 1 si oui 0 sinon*/
int placeVideInventaire(Inventaire *invent, int n);
#endif