/* Auteur : Césaire Agonsè & Nicolas Atrax
 * Création: 21-10-21
 * Modification: 05-01-22 */

#include "../include/perso.h"

Perso* initialisePerso(){
    Perso *perso;
    perso = (Perso *) malloc(sizeof(Perso));

    if (perso == NULL){
        return NULL;
    }

    perso->atk = 10;
    perso->inte = 10;
    perso->def = 10;

    perso->hp = perso->def * 10;
    perso->mp = perso->inte * 10 - 50;

    perso->exp = 0;
    perso->lv = 0;
    perso->bonusExp = 0;

    perso->crit = 5;

    perso->arme = initialiseItem(0, EQUIPEMENT);
    perso->arme->type = VIDE;
    perso->armure = initialiseItem(0, EQUIPEMENT);
    perso->armure->type = VIDE;
    perso->baguette = initialiseItem(0, EQUIPEMENT);
    perso->baguette->type = VIDE;
    perso->popo = initialiseItem(0, POPO);
    perso->popo->type = VIDE;

    perso->modeAtk = MELEE;

    return perso;
}

void affichePerso(Perso *perso){
    assert(perso != NULL);
    printf("Propriété du perso :\n");
    printf("--> Hp  (Health point)     : %d\n", perso->hp);
    printf("--> Mp  (Mana point)       : %d\n", perso->mp);
    printf("--> Atk (Attaque)          : %d\n", perso->atk);
    printf("--> Int (Intelligence)     : %d\n", perso->inte);
    printf("--> Def (Defense)          : %d\n", perso->def);
    printf("--> Exp (experience)       : %d\n", perso->exp);
    printf("--> Lv  (Niveau)           : %d\n", perso->lv);
    printf("--> Crit (Proba coup crit) : %d\n", perso->crit);
}

int niveauSup(Perso *perso){
    assert(perso != NULL);
    while (perso->exp > (perso->lv * 50) + 350){
        if (perso->exp >= (perso->lv * 50) + 350){
            perso->lv ++;
        } else {
            return 0;
        }
    }
    return 1;
}

int attaque(Perso *perso){
    double attaque, alea;
    attaque = perso->atk;

    /*L'attaque est aléatoire entre 80 et 120% (donc 40% de difference et le point 0 est 20)*/
    alea = ((rand() % 40) - 20) / 100.0;
    alea = round(alea * 10) / 10;
    attaque += attaque * alea;
    
    /*Coup critique*/
    if (rand() % 100 < perso->crit){
        attaque *= 3;
    }

    return (int) attaque;
}

int attaqueMagique(Perso *perso){
    double attaque, alea;
    attaque = perso->inte * 2;

    /*L'attaque est aléatoire entre 80 et 120% (donc 40% de difference et le point 0 est 20)*/
    alea = ((rand() % 40) - 20) / 100.0;
    alea = round(alea * 10) / 10;
    attaque += attaque * alea;
    
    /*Coup critique*/
    if (rand() % 100 < perso->crit){
        attaque *= 3;
    }

    if (perso->mp >= 20){
        perso->mp -= 20;
        return (int) attaque;
    }
    
    return 0;
}