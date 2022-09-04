/* Auteur : Césaire Agonsè
 * Création: 21-11-21
 * Modification: 28-11-21 */

#include "../include/item.h"

Item* initialiseItem(int niveau, Type type){
    Item *item;
    item = (Item *) malloc(sizeof(Item));
    
    if (item == NULL){
        return NULL;
    }
    switch (type)
    {
    case VIDE:
        item->type = VIDE;
        item->equipe = -1;
        item->qualite = -1;
        item->actif = -1;
        item->objet.potion = -1;
        item->objet.equipement = -1;
        return item;
        
    case ALEA:
        type = rand() % 2;
        /*on redirige type*/
        switch (type)
        {
        case POPO:
            item->type = type;
            item->objet.potion = rand() % 5;
            if (item->objet.potion != SOIN && item->objet.potion != SOIN){
                item->actif = 30;
            }
            break;

        case EQUIPEMENT:
            item->type = type;
            item->equipe = 0;
            if (niveau > 0){
                item->qualite = rand() % (niveau + 1);
            } else {
                item->qualite = 0;
            }
            
            item->objet.equipement = rand() % 3;
            
            break;
        
        default:
            return NULL;
        }
        break;

    case POPO:
        item->type = type;
        item->objet.potion = rand() % 5;
        if (item->objet.potion != SOIN && item->objet.potion != SOIN){
            item->actif = 30;
        }
        break;

    case EQUIPEMENT:
        item->type = type;
        item->equipe = 0;
        if (niveau > 1){
            item->qualite = rand() % (niveau + 1);
        } else {
            item->qualite = 0;
        }
        
        item->objet.equipement = rand() % 3;
        
        break;
    
    default:
        return NULL;
    }
    return item;
}

Tresor* initialiseTresor(int niveau, Type type){
    Tresor *tresor;
    tresor = (Tresor *) malloc(sizeof(Tresor));
    
    if (tresor == NULL){
        return NULL;
    }
    tresor->first = initialiseItem(niveau, type);
    if (tresor->first == NULL){
        return NULL;
    }
    tresor->second = initialiseItem(niveau, type);
    if (tresor->second == NULL){
        return NULL;
    }

    tresor->vide = 0;
    tresor->ouvert = 0;
    
    return tresor;
}