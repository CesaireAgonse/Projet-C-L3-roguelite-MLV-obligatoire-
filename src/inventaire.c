/* Auteur : Césaire Agonsè
 * Création: 21-11-21
 * Modification: 22-11-21 */

#include "../include/inventaire.h"

int initialiseInventaire(Inventaire *invent){
    int i;
    Item *item;

    for(i = 0; i < NB_ITEM_MAX; i++){
        item = initialiseItem(0,VIDE);
        
        if (item == NULL){
            return 0;
        }
        invent->content[i] = item; 
    }

    return 1;
}

int placeVideInventaire(Inventaire *invent, int n){
    int i, nb_place;
    nb_place = 0;

    for(i = 0; i < NB_ITEM_MAX; i++){
        if (invent->content[i]->type == VIDE){
            nb_place++;
        }
        if (nb_place == n){
            return 1;
        }   
    }
    return 0;
}

int ajouteItem(Inventaire *invent, Item *item){
    int i;

    for(i = 0; i < NB_ITEM_MAX; i++){
        if (invent->content[i]->type == VIDE){
            invent->content[i] = item;
            return 1;
        }
    }    

    return 0;
}

int jetteItem(Inventaire *invent, Item *item){
    int i;

    for(i = 0; i < NB_ITEM_MAX; i++){
        if (invent->content[i] == item){
            /*l'item est perdu à jamais dans le paradis de la mémoire c*/
            free(item);
            invent->content[i] = initialiseItem(0,VIDE);
            return 1;
        }
    }
    return 0;
}