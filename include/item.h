/* Auteur : Césaire Agonsè
 * Création: 22-11-21
 * Modification: 28-11-21 */

#ifndef __ITEM__
#define __ITEM__

#include <stdio.h>
#include <stdlib.h>

typedef enum type{
    POPO,
    EQUIPEMENT,
    VIDE,
    ALEA
} Type;

typedef enum potion{
    SOIN,
    MAGIE,
    REGEN,
    PRECISION,
    APPRENTISSAGE
} Potion;

typedef enum equipement{
    ARMURE,
    ARME,
    BAGUETTE
} Equipement;

typedef struct item {
    Type type;
    int qualite;
    int equipe;
    int actif;
    union Objet {
        Equipement equipement;
        Potion potion;
    } objet;
}Item;

typedef struct tresor{
    struct item *first;
    struct item *second;
    int vide;
    int ouvert;
} Tresor;

/*Initialise un item selon le niveau
* Retourne donc l'item et null si il y a un probleme de malloc
* Le type est du type enum Type */
Item* initialiseItem(int niveau, Type type);

/*Initialise un tresor selon le niveau avec initialiseItem
* Retourne donc le tresor et null si il y a un probleme de malloc
* Le type est du type enum Type */
Tresor* initialiseTresor(int niveau, Type type);

#endif