/* Auteur : Césaire Agonsè & Nicolas Atrax
 * Création: 10-01-22
 * Modification: 10-01-22 */

#include "../include/fichier.h"

int64 initialiser_bit_1(int decalage){
    return (1uLL << decalage);
}

int64 mettre_bit_1(int64 x, int decalage){
   return x | (1uLL << decalage);
}

int64 mettre_bit_0(int64 x, int decalage){
    return x & ~(1uLL << decalage);
}

int tester_bit_1(int64 x, int decalage){
    if (x & (1uLL << decalage)){
        return 1;
    }
    return 0;
}

int64 convertMonstreEnInt64(Cell case_){
    int64 monstreInt;

    monstreInt = 0;
    /*x inscrit sur les 5 premiers bits (1 à 5)*/
    monstreInt = monstreInt | (case_.x);
    /*y inscrit sur les bits 6 à 10*/
    monstreInt = monstreInt | (case_.y << 6);
    /*direction inscrit sur les bits 12 et 13*/
    monstreInt = monstreInt | (case_.surCase.monster->direction << 12);
    /*crti inscrit sur les bits 14 à 17*/
    monstreInt = monstreInt | (case_.surCase.monster->crit << 14);
    /*crti inscrit sur les bits 17 à 32*/
    monstreInt = monstreInt | ((int64) case_.surCase.monster->hp << 17);
    /*crti inscrit sur les bits 32 à 48*/
    monstreInt = monstreInt | ((int64) case_.surCase.monster->atk << 32);
    /*crti inscrit sur les bits 49 à 64*/
    monstreInt = monstreInt | ((int64) case_.surCase.monster->lvl << 49);
    
    return monstreInt;
}

int64 convertTresorEnInt64(Cell case_){
    int64 tresorInt;

    tresorInt = 0;
    /*x inscrit sur les 5 premiers bits (1 à 5)*/
    tresorInt = tresorInt | (case_.x);
    /*y inscrit sur les bits 6 à 10*/
    tresorInt = tresorInt | (case_.y << 6);
    /*ouvert inscrit sur le 12eme bit*/
    tresorInt = tresorInt | (case_.surCase.tresor->ouvert << 12);
    if (case_.surCase.tresor->vide != 1){
        /*premier objet inscrit sur les bits 14 à 37*/
        if (case_.surCase.tresor->first->type != VIDE){
            /*type inscrit sur les bits 14 à 15*/
            tresorInt = tresorInt | (case_.surCase.tresor->first->type << 14);
            /*potion/equipement inscrit sur les bits 16 à 18*/
            if (case_.surCase.tresor->first->type == POPO){
                tresorInt = tresorInt | (case_.surCase.tresor->first->objet.potion << 16);
                /*actif inscrit sur le 21eme bit*/
                tresorInt = tresorInt | (case_.surCase.tresor->first->actif << 21);
            }else if (case_.surCase.tresor->first->type == EQUIPEMENT){
                tresorInt = tresorInt | ((case_.surCase.tresor->first->objet.equipement + 5) << 16);
                /*actif inscrit sur le 19eme bit*/
                tresorInt = tresorInt | (case_.surCase.tresor->first->equipe << 19);
                /*qualite isncrit sur les bits 21 à 37*/
                tresorInt = tresorInt | (case_.surCase.tresor->first->qualite << 21);
            }
        } else {
            /*type inscrit sur les bits 14 à 15*/
            tresorInt = tresorInt | (case_.surCase.tresor->first->type << 14);
        }

        /*deuxieme objet inscrit sur les bits 38 à 60*/
        if (case_.surCase.tresor->second->type != VIDE){
            /*type inscrit sur les bits 38 à 39*/
            tresorInt = tresorInt | ((int64) case_.surCase.tresor->second->type << 38);
            /*potion/equipement inscrit sur les bits 40 à 42*/
            if (case_.surCase.tresor->second->type == POPO){
                tresorInt = tresorInt | ((int64) case_.surCase.tresor->second->objet.potion << 40);
                /*actif inscrit sur le 45eme bit*/
                tresorInt = tresorInt | ((int64) case_.surCase.tresor->second->actif << 45);
            }else if (case_.surCase.tresor->second->type == EQUIPEMENT) {
                tresorInt = tresorInt | (((int64) case_.surCase.tresor->second->objet.equipement + 5) << 40);
                /*actif inscrit sur le 44eme bit*/
                tresorInt = tresorInt | ((int64) case_.surCase.tresor->second->equipe << 43);
                /*qualite isncrit sur les bits 46 à 62*/
                tresorInt = tresorInt | ((int64) case_.surCase.tresor->second->qualite << 45);
            }
        } else {
            /*type inscrit sur les bits 38 à 39*/
            tresorInt = tresorInt | ((int64) case_.surCase.tresor->first->type << 38);
        }
    } else {return 0;}

    return tresorInt;
}

int convertInt64EnInt(int64 n, int firstBit, int lastBit){
    int64 result;
    int i;
    result = 0;

    result = n >> (firstBit - 1);

    for (i = lastBit - (firstBit) + 1; i < 64; i++){
        result = mettre_bit_0(result, i);
    }

    return (unsigned int) result;
}

int64 *convertPlateauEnLigne(Plateau *plateau, Celltype type){
    int i, j;
    
    int64 ligne;
    int64 *colonne;

    colonne = (int64 *) malloc(sizeof(int64) * HAUTEUR);
    ligne = 0;
    for (j = 0; j < HAUTEUR; j++){
        ligne = 0;
        for (i = 0; i < LARGEUR; i++){
            if (plateau->grille[i][j].type == type){
                ligne = mettre_bit_1(ligne, i);
            }
        }
        colonne[j] = ligne;
    }

    return colonne;
}

int saveEtage(Plateau **plateau, int nbEtage){
    int i,j, nbMonstre;
    FILE *sauvegarde = NULL;
    int64 *colonne;
    char nomFichier[HAUTEUR * 20 + 22];

    snprintf(nomFichier, sizeof(nomFichier), "save/donjon/etage%d.txt", nbEtage);

    nbMonstre = 0;
    colonne = (int64 *) malloc(sizeof(int64) * HAUTEUR);
    sauvegarde = fopen(nomFichier, "w");

    if (sauvegarde != NULL){
        
        printf("save de l'etage %d\n", nbEtage);
        /*case de salle*/
        colonne = convertPlateauEnLigne(plateau[nbEtage], ROOM);
        
        for (j = 0; j < HAUTEUR; j++){
            if (j ==0){
                fprintf(sauvegarde,"%lld", colonne[j]);
            }else {
                fprintf(sauvegarde,",%lld", colonne[j]);
            }
            
        }
        fprintf(sauvegarde, "\n");
        
        /*monstres*/
        for (i = 1; i < LARGEUR; i++){
            for(j = 1; j < HAUTEUR; j++){
                if (plateau[nbEtage]->grille[i][j].type == MONSTER){
                    if(nbMonstre == 0){
                        fprintf(sauvegarde, "%lld", convertMonstreEnInt64(plateau[nbEtage]->grille[i][j]));
                    }else {
                        fprintf(sauvegarde, ",%lld", convertMonstreEnInt64(plateau[nbEtage]->grille[i][j]));
                    }
                    nbMonstre++;
                }
            }
        }
        fprintf(sauvegarde, "\n");
        nbMonstre = 0;

        /*tresors*/
        for (i = 1; i < LARGEUR; i++){
            for(j = 1; j < HAUTEUR; j++){
                if (plateau[nbEtage]->grille[i][j].type == TREASURE){
                    if(nbMonstre == 0){
                        fprintf(sauvegarde, "%lld", convertTresorEnInt64(plateau[nbEtage]->grille[i][j]));
                    }else {
                        fprintf(sauvegarde, ",%lld", convertTresorEnInt64(plateau[nbEtage]->grille[i][j]));
                    }
                    nbMonstre++;        
                }
            }
        }
        fprintf(sauvegarde, "\n");
        nbMonstre = 0;

        if (plateau[nbEtage]->grille[1][1].type == STAIR_DOWN){
            fprintf(sauvegarde, "0\n");
        } else if (plateau[nbEtage]->grille[LARGEUR - 2][1].type == STAIR_DOWN){
            fprintf(sauvegarde, "1\n");
        } else if (plateau[nbEtage]->grille[LARGEUR - 2][HAUTEUR - 2].type == STAIR_DOWN){
            fprintf(sauvegarde, "2\n");
        } else if (plateau[nbEtage]->grille[1][HAUTEUR - 2].type == STAIR_DOWN){
            fprintf(sauvegarde, "3\n");
        }    
        

    } else {
        fprintf(stderr, "Erreur >> Sauvegarde impossible dans saveEtage%d\n", nbEtage);
        return 0;
    }
    free(colonne);
    fclose(sauvegarde);
    return 1;
}

int chargerEtage(Plateau **plateau, int nbEtage){
    int i, j;
    FILE *sauvegarde = NULL;
    char *colonneStr, *ligneStr;
    char *ligneMonstre, *monstre;
    char *ligneTresor, *tresor;
    char *ligneStair;
    char nomFichier[HAUTEUR * 20 + 22];

    snprintf(nomFichier, sizeof(nomFichier), "save/donjon/etage%d.txt", nbEtage);
    
    colonneStr = (char *) malloc(sizeof(char) * HAUTEUR * 20);
    ligneStr = (char *) malloc(sizeof(char) * 20);

    ligneMonstre = (char *) malloc(sizeof(char) * NB_MONSTRE *(11 + 20));
    monstre = (char *) malloc(sizeof(char) * 65);
    
    ligneTresor = (char *) malloc(sizeof(char) * (NB_MONSTRE + 1) *(11 + 20));
    tresor = (char *) malloc(sizeof(char) * 65);

    ligneStair = (char *) malloc(sizeof(char) * 2);

    sauvegarde = fopen(nomFichier, "r");

    if (sauvegarde != NULL){
        printf("chargement de l'etage %d\n", nbEtage);

        /*case de salle*/
        fgets(colonneStr, 20 * HAUTEUR, sauvegarde);     
        for (j = 0; j < HAUTEUR; j++){
            if (j == 0){
                ligneStr = strtok(colonneStr,",");
            } else {
                ligneStr = strtok(NULL,",");
            }
            for (i = 0; i < LARGEUR; i++){
                if (tester_bit_1(atoll(ligneStr), i)){
                    plateau[nbEtage]->grille[i][j].type = ROOM;
                }
            }
        }

        /*monstres*/
        fgets(ligneMonstre, NB_MONSTRE *(11 + 20), sauvegarde);
        for (i = 0; monstre != NULL; i++){
            if (i != 0){
                monstre = strtok(NULL,",");
            }else{
                monstre = strtok(ligneMonstre,",");
            }
            if (monstre == NULL){
                break;
            }
            
            plateau[nbEtage]->grille[convertInt64EnInt(atoll(monstre), 1, 6)][convertInt64EnInt(atoll(monstre), 7, 12)].type = MONSTER;
            plateau[nbEtage]->grille[convertInt64EnInt(atoll(monstre), 1, 6)][convertInt64EnInt(atoll(monstre), 7, 12)].surCase.monster = initialiseMonstre(0);
            plateau[nbEtage]->grille[convertInt64EnInt(atoll(monstre), 1, 6)][convertInt64EnInt(atoll(monstre), 7, 12)].surCase.monster->direction = convertInt64EnInt(atoll(monstre), 13, 14);
            plateau[nbEtage]->grille[convertInt64EnInt(atoll(monstre), 1, 6)][convertInt64EnInt(atoll(monstre), 7, 12)].surCase.monster->crit = convertInt64EnInt(atoll(monstre), 15, 17);
            plateau[nbEtage]->grille[convertInt64EnInt(atoll(monstre), 1, 6)][convertInt64EnInt(atoll(monstre), 7, 12)].surCase.monster->hp = convertInt64EnInt(atoll(monstre), 18, 32);
            plateau[nbEtage]->grille[convertInt64EnInt(atoll(monstre), 1, 6)][convertInt64EnInt(atoll(monstre), 7, 12)].surCase.monster->atk = convertInt64EnInt(atoll(monstre), 33, 49);
            plateau[nbEtage]->grille[convertInt64EnInt(atoll(monstre), 1, 6)][convertInt64EnInt(atoll(monstre), 7, 12)].surCase.monster->lvl = convertInt64EnInt(atoll(monstre), 50, 64);
        }
        
        /*tresor*/
        fgets(ligneTresor, (NB_MONSTRE + 1) *(11 + 20), sauvegarde);
        for (i = 0; tresor != NULL; i++){
            if (i != 0){
                tresor = strtok(NULL,",");
            }else{
                tresor = strtok(ligneTresor,",");
            }
            if (tresor == NULL){
                break;
            }
            plateau[nbEtage]->grille[convertInt64EnInt(atoll(tresor), 1, 6)][convertInt64EnInt(atoll(tresor), 7, 12)].type = TREASURE;
            plateau[nbEtage]->grille[convertInt64EnInt(atoll(tresor), 1, 6)][convertInt64EnInt(atoll(tresor), 7, 12)].surCase.tresor = (Tresor *) malloc(sizeof(Tresor));
            plateau[nbEtage]->grille[convertInt64EnInt(atoll(tresor), 1, 6)][convertInt64EnInt(atoll(tresor), 7, 12)].surCase.tresor->ouvert = convertInt64EnInt(atoll(tresor), 12, 12);
            if (convertInt64EnInt(atoll(tresor), 13, 13) != VIDE){
                plateau[nbEtage]->grille[convertInt64EnInt(atoll(tresor), 1, 6)][convertInt64EnInt(atoll(tresor), 7, 12)].surCase.tresor->first = initialiseItem(0,VIDE);
                plateau[nbEtage]->grille[convertInt64EnInt(atoll(tresor), 1, 6)][convertInt64EnInt(atoll(tresor), 7, 12)].surCase.tresor->first->type = convertInt64EnInt(atoll(tresor), 15, 16);
                if (plateau[nbEtage]->grille[convertInt64EnInt(atoll(tresor), 1, 6)][convertInt64EnInt(atoll(tresor), 7, 12)].surCase.tresor->first->type == EQUIPEMENT){
                    plateau[nbEtage]->grille[convertInt64EnInt(atoll(tresor), 1, 6)][convertInt64EnInt(atoll(tresor), 7, 12)].surCase.tresor->first->objet.equipement = convertInt64EnInt(atoll(tresor), 17, 19) - 5;
                    plateau[nbEtage]->grille[convertInt64EnInt(atoll(tresor), 1, 6)][convertInt64EnInt(atoll(tresor), 7, 12)].surCase.tresor->first->equipe = convertInt64EnInt(atoll(tresor), 20, 20);
                    plateau[nbEtage]->grille[convertInt64EnInt(atoll(tresor), 1, 6)][convertInt64EnInt(atoll(tresor), 7, 12)].surCase.tresor->first->qualite = convertInt64EnInt(atoll(tresor), 22, 38);
                } else if (plateau[nbEtage]->grille[convertInt64EnInt(atoll(tresor), 1, 6)][convertInt64EnInt(atoll(tresor), 7, 12)].surCase.tresor->first->type == POPO){
                    plateau[nbEtage]->grille[convertInt64EnInt(atoll(tresor), 1, 6)][convertInt64EnInt(atoll(tresor), 7, 12)].surCase.tresor->first->objet.potion = convertInt64EnInt(atoll(tresor), 17, 19);
                    plateau[nbEtage]->grille[convertInt64EnInt(atoll(tresor), 1, 6)][convertInt64EnInt(atoll(tresor), 7, 12)].surCase.tresor->first->actif = convertInt64EnInt(atoll(tresor), 22, 37);
                } else {
                }
            }
            if (convertInt64EnInt(atoll(tresor), 38, 38) != VIDE){
                plateau[nbEtage]->grille[convertInt64EnInt(atoll(tresor), 1, 6)][convertInt64EnInt(atoll(tresor), 7, 12)].surCase.tresor->second = initialiseItem(0,VIDE);
                plateau[nbEtage]->grille[convertInt64EnInt(atoll(tresor), 1, 6)][convertInt64EnInt(atoll(tresor), 7, 12)].surCase.tresor->second->type = convertInt64EnInt(atoll(tresor), 39, 40);
                if (plateau[nbEtage]->grille[convertInt64EnInt(atoll(tresor), 1, 6)][convertInt64EnInt(atoll(tresor), 7, 12)].surCase.tresor->second->type == EQUIPEMENT){
                    plateau[nbEtage]->grille[convertInt64EnInt(atoll(tresor), 1, 6)][convertInt64EnInt(atoll(tresor), 7, 12)].surCase.tresor->second->objet.equipement = convertInt64EnInt(atoll(tresor), 41, 43) - 5;
                    plateau[nbEtage]->grille[convertInt64EnInt(atoll(tresor), 1, 6)][convertInt64EnInt(atoll(tresor), 7, 12)].surCase.tresor->second->equipe = convertInt64EnInt(atoll(tresor), 44, 44);
                    plateau[nbEtage]->grille[convertInt64EnInt(atoll(tresor), 1, 6)][convertInt64EnInt(atoll(tresor), 7, 12)].surCase.tresor->second->qualite = convertInt64EnInt(atoll(tresor), 46, 62);
                } else if (plateau[nbEtage]->grille[convertInt64EnInt(atoll(tresor), 1, 6)][convertInt64EnInt(atoll(tresor), 7, 12)].surCase.tresor->second->type == POPO) {
                    plateau[nbEtage]->grille[convertInt64EnInt(atoll(tresor), 1, 6)][convertInt64EnInt(atoll(tresor), 7, 12)].surCase.tresor->second->objet.potion = convertInt64EnInt(atoll(tresor), 41, 43);
                    plateau[nbEtage]->grille[convertInt64EnInt(atoll(tresor), 1, 6)][convertInt64EnInt(atoll(tresor), 7, 12)].surCase.tresor->second->actif = convertInt64EnInt(atoll(tresor), 46, 37);
                } else {
                }
            }
        }
        
        fgets(ligneStair, 2, sauvegarde);
        if (atoi(ligneStair) == 0){
            plateau[nbEtage]->grille[1][1].type = STAIR_DOWN;
        } else if (atoi(ligneStair) == 1){
            plateau[nbEtage]->grille[LARGEUR - 2][1].type = STAIR_DOWN;
        } else if (atoi(ligneStair) == 2){
            plateau[nbEtage]->grille[LARGEUR - 2][HAUTEUR - 2].type = STAIR_DOWN;
        } else if (atoi(ligneStair) == 3){
            plateau[nbEtage]->grille[1][HAUTEUR - 2].type = STAIR_DOWN;
        }
        plateau[nbEtage]->grille[LARGEUR / 2][HAUTEUR / 2].type = STAIR_UP;
        
        
        
    } else {
        fprintf(stderr, "Erreur >> Chargement impossible dans ChargerEtage%d\n", nbEtage);
        return 0;
    }
    return 1;
}

int64 convertPersoEnInt64(int hp_def_bonus_exp, int mp_exp_mode_atk, int atk_lv, int inte_crit){
    int64 n;

    n = 0;
    /*hp, def ou bonus_exp inscrit sur les 16 premiers bits (1 à 16)*/
    n = n | ((int64) hp_def_bonus_exp);
    /*mp_exp, exp ou mode_atk inscrit sur les bits 17 à 32*/
    n = n | ((int64) mp_exp_mode_atk << 17);
    /*atk_lv inscrit sur les bits 33 à 48*/
    n = n | ((int64) atk_lv << 33);
    /*inte_crit inscrit sur les bits 49 à 64*/
    n = n | ((int64) inte_crit << 49);

    return n;
}

int64 convertItemEnInt64(Item *item){
    int64 n;
    n = 0;
    /*type inscrit sur les bits 1 à 2*/
    n = n | (item->type);
    /*potion/equipement inscrit sur les bits 3 à 6*/
    if (item->type == POPO){
        n = n | ((int64) item->objet.potion << 3);
        /*actif inscrit sur le 9eme bit*/
        n = n | ((int64) item->actif << 9);
    }else if (item->type == EQUIPEMENT){
        n = n | ((int64) (item->objet.equipement + 5) << 3);
        /*actif inscrit sur le 7eme bit*/
        n = n | ((int64) item->equipe << 7);
        /*qualite isncrit sur les bits 9 à 25*/
        n = n | ((int64) item->qualite << 9);
    }

    return n;
}

Item *convertInt64EnItem(int64 n){
    Item *item;

    item =initialiseItem(0,VIDE);
    item->type = convertInt64EnInt(n, 1, 2);
    if (convertInt64EnInt(n, 1, 3) == VIDE){
        return item;
    } else if (convertInt64EnInt(n, 1, 3) == POPO){
        item->objet.potion = convertInt64EnInt(n, 4, 7);
        item->actif = convertInt64EnInt(n, 10, 16);
    } else if (convertInt64EnInt(n, 1, 3) == EQUIPEMENT){
        item->objet.equipement = convertInt64EnInt(n, 4, 7) - 5;
        item->equipe = convertInt64EnInt(n, 7, 7);
        item->qualite = convertInt64EnInt(n, 9, 25);
    }
    
    return item;
}

int savePerso(Perso *perso){
    FILE *sauvegarde = NULL;

    sauvegarde = fopen("save/Perso.txt", "w");

    if (sauvegarde != NULL){
        fprintf(sauvegarde, "%lld\n", convertPersoEnInt64(perso->hp, perso->mp, perso->atk, perso->inte));
        fprintf(sauvegarde, "%lld\n", convertPersoEnInt64(perso->def, perso->exp, perso->lv, perso->crit));
        fprintf(sauvegarde, "%lld\n", convertPersoEnInt64(perso->bonusExp, perso->modeAtk, 0, 0));
        fprintf(sauvegarde,"%lld\n", convertItemEnInt64(perso->armure));
        fprintf(sauvegarde,"%lld\n", convertItemEnInt64(perso->arme));
        fprintf(sauvegarde,"%lld\n", convertItemEnInt64(perso->baguette));
        fprintf(sauvegarde,"%lld\n", convertItemEnInt64(perso->popo));
    } else {
        fprintf(stderr, "Erreur >> Sauvegarde impossible dans savePerso\n");
        return 0;
    }
    fclose(sauvegarde);

    return 1;
}

int chargerPerso(Perso *perso){
    FILE *sauvegarde = NULL;
    char *nombre;

    nombre = (char *) malloc(sizeof(char) * 20);

    sauvegarde = fopen("save/Perso.txt", "r");

    if (sauvegarde != NULL){
        fgets(nombre, 20,sauvegarde);
        perso->hp = convertInt64EnInt(atoll(nombre), 1, 17);
        perso->mp = convertInt64EnInt(atoll(nombre), 18, 33);
        perso->atk = convertInt64EnInt(atoll(nombre), 34, 49);
        perso->inte = convertInt64EnInt(atoll(nombre), 50, 64);
        fgets(nombre, 20,sauvegarde);
        perso->def = convertInt64EnInt(atoll(nombre), 1, 17);
        perso->exp = convertInt64EnInt(atoll(nombre), 18, 33);
        perso->lv = convertInt64EnInt(atoll(nombre), 34, 49);
        perso->crit = convertInt64EnInt(atoll(nombre), 50, 64);
        fgets(nombre, 20,sauvegarde);
        perso->bonusExp = convertInt64EnInt(atoll(nombre), 1, 17);
        perso->modeAtk = convertInt64EnInt(atoll(nombre), 18, 33);

        fgets(nombre, 20,sauvegarde);
        perso->armure = convertInt64EnItem(atoll(nombre));
        fgets(nombre, 20,sauvegarde);
        perso->arme = convertInt64EnItem(atoll(nombre));
        fgets(nombre, 20,sauvegarde);
        perso->baguette = convertInt64EnItem(atoll(nombre));
        fgets(nombre, 20,sauvegarde);
        perso->popo = convertInt64EnItem(atoll(nombre));
    } else {
        fprintf(stderr, "Erreur >> Charegment de la sauvegarde impossible dans chargerPerso\n");
        return 0;
    }
    fclose(sauvegarde);

    return 1;
}

int savePosition(Position *position){
    FILE *sauvegarde = NULL;
    int64 n1, n2;

    sauvegarde = fopen("save/Position.txt", "w");

    if (sauvegarde != NULL){
        n1 = 0;
        /*x inscrit sur les 16 premiers bits (1 à 16)*/
        n1 = n1 | ((int64) position->x);
        /*y inscrit sur les bits 17 à 32*/
        n1 = n1 | ((int64) position->y << 17);
        /*direction inscrit sur les bits 33 et 34*/
        n1 = n1 | ((int64) position->direction << 33);

        fprintf(sauvegarde,"%lld\n", n1);
        
        n2 = 0;
        /*x inscrit sur les 16 premiers bits (1 à 32)*/
        n2 = n2 | ((int64) position->etage);
        /*y inscrit sur les bits 33 à 64*/
        n2 = n2 | ((int64) position->nbEtageMax << 33);
        fprintf(sauvegarde,"%lld\n", n2);

    } else {
        fprintf(stderr, "Erreur >> Sauvegarde impossible dans savePosition\n");
        return 0;
    }
    fclose(sauvegarde);

    return 1;
}

int chargerPosition(Position *position){
    FILE *sauvegarde = NULL;
    char *nombre;

    nombre = (char *) malloc(sizeof(char) * 20);

    sauvegarde = fopen("save/Position.txt", "r");

    if (sauvegarde != NULL){
        fgets(nombre, 20,sauvegarde);
        position->x = convertInt64EnInt(atoll(nombre), 1, 17);
        position->y = convertInt64EnInt(atoll(nombre), 18, 33);
        position->direction = convertInt64EnInt(atoll(nombre), 33, 34);

        fgets(nombre, 20,sauvegarde);
        position->etage = convertInt64EnInt(atoll(nombre), 1, 32);
        position->nbEtageMax = convertInt64EnInt(atoll(nombre), 33, 64);

    } else {
        fprintf(stderr, "Erreur >> Sauvegarde impossible dans savePosition\n");
        return 0;
    }
    fclose(sauvegarde);

    return 1;
}

int saveInventaire(Inventaire *inventaire){
    FILE *sauvegarde = NULL;
    int i;
    
    sauvegarde = fopen("save/Inventaire.txt", "w");

    if (sauvegarde != NULL){
        for (i = 0; i < NB_ITEM_MAX; i++){
            fprintf(sauvegarde,"%lld\n", convertItemEnInt64(inventaire->content[i]));
        }
    } else {
        fprintf(stderr, "Erreur >> Sauvegarde impossible dans saveInventaire\n");
        return 0;
    }
    fclose(sauvegarde);

    return 1;
}

int chargerInventaire(Inventaire *inventaire){
    FILE *sauvegarde = NULL;
    int i;
    char *nombre;

    nombre = (char *) malloc(sizeof(char) * 20);
    sauvegarde = fopen("save/Inventaire.txt", "r");

    if (sauvegarde != NULL){
        for (i = 0; i < NB_ITEM_MAX; i++){
            fgets(nombre, 20, sauvegarde);
            inventaire->content[i] = convertInt64EnItem(atoll(nombre));
        }
    } else {
        fprintf(stderr, "Erreur >> Sauvegarde impossible dans chargerInventaire\n");
        return 0;
    }
    fclose(sauvegarde);

    return 1;
}