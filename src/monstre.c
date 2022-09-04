#include "../include/monstre.h"

Monstre* initialiseMonstre(int niveau){
    Monstre *monstre;
    double alea;
    monstre = (Monstre *) malloc(sizeof(Monstre));

    if (monstre == NULL){
        return NULL;
    }

    /*Faire de l'aléatoire pour atk et hp*/
    monstre->direction = EAST;
    
    monstre->atk = 10 + (niveau * 2);
    alea = ((rand() % 40) - 20) / 100.0;
    alea = round(alea * 10) / 10;
    monstre->atk += monstre->atk * alea;
    
    monstre->hp = 10 + (niveau * 2);
    alea = ((rand() % 40) - 20) / 100.0;
    alea = round(alea * 10) / 10;
    monstre->hp += monstre->hp * alea;

    monstre->lvl = niveau;

    monstre->crit = 5;

    return monstre;
}

void afficheMonstre(Monstre *monstre){
    assert(monstre != NULL);
    printf("Propriété du monstre :\n");
    printf("--> Hp  (Health point)     : %d\n", monstre->hp);
    printf("--> Atk (Attaque)          : %d\n", monstre->atk);
    printf("--> Crit (Proba coup crit) : %d\n", monstre->crit);
    printf("--> direction              : %d\n", monstre->direction);
}


int attaqueMonstre(Monstre *monstre){
    double attaque, alea;
    attaque = monstre->atk;
    
    /*L'attaque est aléatoire entre 80 et 120% (donc 40% de difference et le point 0 est 20)*/
    alea = ((rand() % 40) - 20) / 100.0;
    alea = round(alea * 10) / 10;
    attaque += attaque * alea;
    
    /*Coup critique*/
    if (rand() % 100 < monstre->crit){
        attaque *= 3;
    }

    return (int) attaque;
}


