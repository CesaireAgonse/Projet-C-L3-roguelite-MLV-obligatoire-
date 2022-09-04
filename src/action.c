/* Auteur : Césaire Agonsè
 * Création: 21-11-21
 * Modification: 05-01-22 */

#include "../include/action.h"

int fouilleTresor(Inventaire *invent, Tresor *tresor){
    
    if (tresor->vide == 1){
        return 0;
    }
    tresor->ouvert = 1;
    if (placeVideInventaire(invent, 2)){
        if (!ajouteItem(invent, tresor->first)){
            return 0;
        }

        if (tresor->second == NULL){
            tresor->vide = 1;
            return 1;
        } else {
            if (!ajouteItem(invent, tresor->second)){
                return 0;
            }
            tresor->vide = 1;
        }
        
    } else if (placeVideInventaire(invent, 1)) {
        
        if (!ajouteItem(invent, tresor->first)){
            return 0;
        }

        if (tresor->second == NULL){
            tresor->vide = 1;
            return 1;
        } else {
            tresor->first = tresor->second;
            tresor->second = NULL;
        }
    } else {
    }

    return 1;
}

int deplacePerso(Position *position, Plateau *etage, Direction direction){
    Cell *case_;
    case_ = (Cell *) malloc(sizeof(Cell));
    case_->x = position->x;
    case_->y = position->y;

    switch (direction)
    {
    case NORTH:
        if (caseAdjacente(etage, case_, direction, ROOM) != NULL){
            position->y -= 1;
        } else if (caseAdjacente(etage, case_, direction, STAIR_DOWN) != NULL){
            position->y -= 1;
        } else if (caseAdjacente(etage, case_, direction, STAIR_UP) != NULL){
            position->y -= 1;
        } else {
            return 0;
        }
            
        break;
    case EAST:
        if (caseAdjacente(etage, case_, direction, ROOM) != NULL){
            position->x += 1;
        } else if (caseAdjacente(etage, case_, direction, STAIR_DOWN) != NULL){
            position->x += 1;
        } else if (caseAdjacente(etage, case_, direction, STAIR_UP) != NULL){
            position->x += 1;
        } else {
            return 0;
        }
            
        break;
    case SOUTH:
        if (caseAdjacente(etage, case_, direction, ROOM) != NULL){
            position->y -= 1;
        } else if (caseAdjacente(etage, case_, direction, STAIR_DOWN) != NULL){
            position->y -= 1;
        } else if (caseAdjacente(etage, case_, direction, STAIR_UP) != NULL){
            position->y -= 1;
        } else {
            return 0;
        }
            
        break;
    case WEST:
        if (caseAdjacente(etage, case_, direction, ROOM) != NULL){
            position->x -= 1;
        } else if (caseAdjacente(etage, case_, direction, STAIR_DOWN) != NULL){
            position->x -= 1;
        } else if (caseAdjacente(etage, case_, direction, STAIR_UP) != NULL){
            position->x -= 1;
        } else {
            return 0;
        }
            
        break;
    
    default:
        fprintf(stderr, "Erreur >> Direction inconnue dans deplacePerso : %d", direction);
        return 0;
        break;
    }
    return 1;
}

void subitAttaque(Perso *perso, Monstre *monstre){
    perso->hp -= attaqueMonstre(monstre);
}

void lanceAttaque(Perso *perso, Monstre *monstre){
    if (perso->modeAtk == MAGIC){
        monstre->hp -= attaqueMagique(perso);    
    } else {
        monstre->hp -= attaque(perso);
    }
}

void supprimerMonstres(Plateau *etage, Perso *perso){
    int i, j;
    Tresor *tresor;
    for (i = 0; i < LARGEUR; i++){
        for (j = 0; j < HAUTEUR; j++){
            if (etage->grille[i][j].type == MONSTER){
                /*Si le monstre n'a plus de vie alors la case devient un trésor
                * et laisse donc apparaitre le tresor*/
                if (etage->grille[i][j].surCase.monster->hp <= 0){
                    /*free(&etage->grille[i][j].surCase.monster);*/
                    etage->grille[i][j].surCase.monster = NULL;
                    etage->grille[i][j].type = TREASURE;
                    tresor = initialiseTresor(etage->niveau, ALEA);
                    etage->grille[i][j].surCase.tresor = tresor;
                    perso->exp += (10 * etage->niveau + 5) * (100 + perso->bonusExp) / 100;
                }
            }
        }
    }
    
}

void supprimerTresors(Plateau *etage){
    int i, j;

    for (i = 0; i < LARGEUR; i++){
        for (j = 0; j < HAUTEUR; j++){
            if (etage->grille[i][j].type == TREASURE){
                if (etage->grille[i][j].surCase.tresor->vide == 1){
                    /*free(&etage->grille[i][j].surCase.tresor);*/
                    etage->grille[i][j].surCase.tresor = NULL;
                    etage->grille[i][j].type = ROOM;
                }
            }
        }
    }
}

void monstreAttaque(Perso *perso, Position position, Plateau *etage){
    Cell *monstre_potentiel;

    monstre_potentiel = caseAdjacente(etage, &etage->grille[position.x][position.y], NORTH, 1);
    if (monstre_potentiel->type == MONSTER){
        subitAttaque(perso, monstre_potentiel->surCase.monster);
        monstre_potentiel->surCase.monster->direction = SOUTH;
    }
    monstre_potentiel = caseAdjacente(etage, &etage->grille[position.x][position.y], EAST, 1);
    if (monstre_potentiel->type == MONSTER){
        subitAttaque(perso, monstre_potentiel->surCase.monster);
        monstre_potentiel->surCase.monster->direction = WEST;
    }
    monstre_potentiel = caseAdjacente(etage, &etage->grille[position.x][position.y], SOUTH, 1);
    if (monstre_potentiel->type == MONSTER){
        subitAttaque(perso, monstre_potentiel->surCase.monster);
        monstre_potentiel->surCase.monster->direction = NORTH;
    }
    monstre_potentiel = caseAdjacente(etage, &etage->grille[position.x][position.y], WEST, 1);
    if (monstre_potentiel->type == MONSTER){
        subitAttaque(perso, monstre_potentiel->surCase.monster);
        monstre_potentiel->surCase.monster->direction = EAST;
    }
}

void remplaceItemActif(Perso *perso, Item *item){
    switch (item->type)
    {
    case POPO:
        /*Pour l'instant on ne peut avoir qu'une seule potion active*/
        
        switch (item->objet.potion)
        {
        case SOIN:
            perso->crit = 5;
            perso->bonusExp = 0;
            perso->hp += (perso->def * 10) / 10;
            if (perso->hp > (perso->def * 10)){
                perso->hp = (perso->def * 10);
            }
            break;

        case MAGIE:
            perso->crit = 5;
            perso->bonusExp = 0;
            perso->mp += (perso->inte * 10 - 50) / 10;
            if (perso->mp > (perso->inte * 10 - 50)){
                perso->mp = (perso->inte * 10 - 50);
            }
            break;

        case REGEN:
            perso->crit = 5;
            perso->bonusExp = 0;
            free(perso->popo);
            perso->popo = item;
            break;

        case PRECISION:
            perso->bonusExp = 0;
            free(perso->popo);
            perso->popo = item;
            perso->crit = 15;
            break;

        case APPRENTISSAGE:
            perso->crit = 5;
            free(perso->popo);
            perso->popo = item;
            perso->bonusExp = 30;
            break;

        default:
            fprintf(stderr, "Erreur >> Potion inconnue dans RemplaceItemActif : %d\n", item->objet.potion);
            break;
        }
        break;

    case EQUIPEMENT:
        switch (item->objet.equipement)
        {
        case ARME:
            perso->atk = 10 + (5 * perso->lv);
            free(perso->arme);
            perso->arme = item;
            perso->atk += 5 + (5 * perso->arme->qualite);
            break;
        
        case ARMURE:
            perso->def = 10 + (5 * perso->lv);
            free(perso->armure);
            perso->armure = item;
            perso->def += 5 + (5 * perso->armure->qualite);
            break;

        case BAGUETTE:
            perso->inte = 10 + (5 * perso->lv);
            free(perso->baguette);
            perso->baguette = item;
            perso->inte += 5 + (5 * perso->baguette->qualite);
            break;
        
        default:
            fprintf(stderr, "Erreur >> Equipement inconnu dans RemplaceItemActif : %d\n", item->objet.equipement);
            break;
        }
        break;
    
    default:
        fprintf(stderr, "Erreur >> Type de l'item incoonu dans RemplaceItemActif : %d\n", item->type);
        break;
    }
}

void equipeItem(Perso *perso, Inventaire *invent, Item *item){
    int i;

    for(i = 0; i < NB_ITEM_MAX; i++){
        
        if (invent->content[i] == item){
            /*l'item est perdu à jamais dans le paradis de la mémoire c*/
            remplaceItemActif(perso, item);
            invent->content[i] = initialiseItem(0,VIDE);
            break;
        }
    }
}

void actualiseEffetPotion(Perso *perso){
    if (perso->popo->type != VIDE){
        switch (perso->popo->objet.potion)
        {
        case REGEN:
            if (perso->popo->actif % 3 == 0){
                perso->hp += 20;
                perso->mp += 10;
            }
            perso->popo->actif -= 1;
            if (perso->popo->actif <= 0){
                free(perso->popo);
                perso->popo = initialiseItem(0,VIDE);
            }
            if (perso->hp > (perso->def * 10)){
                perso->hp = (perso->def * 10);
            }
            if (perso->mp > (perso->inte * 10 - 50)){
                perso->mp = (perso->inte * 10 - 50);
            }
            
            break;

        case PRECISION:
            perso->popo->actif -= 1;
            if (perso->popo->actif <= 0){
                perso->crit = 5;
                free(perso->popo);
                perso->popo = initialiseItem(0,VIDE);
            }
            break;

        case APPRENTISSAGE:
            perso->popo->actif -= 1;
            if (perso->popo->actif <= 0){
                perso->bonusExp = 0;
                free(perso->popo);
                perso->popo = initialiseItem(0,VIDE);
            }
            break;
        
        default:
            fprintf(stderr, "Erreur >> Type de potion inconnu dans ActualiseEffetPotion : %d\n", perso->popo->objet.potion);
            break;
        }
    }
    
}

void actualiseEquipement(Perso *perso, Inventaire *invent){
    int i;

    for (i = 0; i < NB_ITEM_MAX; i++){
        if (invent->content[i]->type == EQUIPEMENT){
            switch (invent->content[i]->objet.equipement)
            {
            case ARME:
                if (perso->arme->type == VIDE || perso->arme->qualite < invent->content[i]->qualite){
                    equipeItem(perso, invent, invent->content[i]);
                }
                break;
            
            case ARMURE:
                if (perso->armure->type == VIDE || perso->armure->qualite < invent->content[i]->qualite){
                    equipeItem(perso, invent, invent->content[i]);
                }
                break;

            case BAGUETTE:
                if (perso->baguette->type == VIDE || perso->baguette->qualite < invent->content[i]->qualite){
                    equipeItem(perso, invent, invent->content[i]);
                }
                break;
            
            default:
                fprintf(stderr, "Erreur >> Type d'equipement inconnu dans ActualiseEquipement : %d\n", invent->content[i]->objet.equipement);
                break;
            }
            
        }
    }
}

int effectuerTour(Plateau **plateau, Perso *perso, Position *position, Inventaire *invent, int direction){
    Cell *destination;

    if (direction >= 4 || direction < 0){
        fprintf(stderr,"Erreur >> Direction inconnue dans effectuerTour : %d\n", direction);
        return -1;
    } else {
        destination = caseAdjacente(plateau[position->etage], &plateau[position->etage]->grille[position->x][position->y], direction, 1);
        if (destination->type == ROOM || destination->type == STAIR_UP || destination->type == STAIR_DOWN){
            deplacerJoueur(*plateau[position->etage], position, direction);
        } else if (destination->type == MONSTER){
            lanceAttaque(perso, destination->surCase.monster);
        } else if (destination->type == TREASURE){
            if (fouilleTresor(invent, destination->surCase.tresor) == 0){
                fprintf(stderr,"Erreur >> Probleme lors de la fouille du tresor\n");
                return -1;
            }        
        }
        /*On enleve les monstres morts et les coffres vides*/
        supprimerTresors(plateau[position->etage]);
        supprimerMonstres(plateau[position->etage], perso);
            
        /*Si jamais les monstres adjacents attaque le hero*/
        monstreAttaque(perso, *position, plateau[position->etage]);

        actualiseEffetPotion(perso);
        actualiseEquipement(perso, invent);
        niveauSup(perso);
        /*Verifier la vie du perso*/
        if (perso->hp < 1){
            return 0;
        }
        
        
        
        
        
    }

    return 1;
}

int changeEtage(Plateau **plateau, Position *position){
    int i, j;
    if (position->nbEtageMax < 0 || position->etage < 0){
        fprintf(stderr, "Erreur >> Parametre invalide dans changeEtage\n");
        return -2;
    }

    switch (plateau[position->etage]->grille[position->x][position->y].type)
    {
    case STAIR_UP:
        if (position->etage > 0){
            position->etage--;
            for (i = 0; i < LARGEUR; i++){
                for(j = 0; j < HAUTEUR; j++){
                    if (plateau[position->etage]->grille[i][j].type == STAIR_DOWN){
                        position->x = i;
                        position->y = j;
                    }
                }
            }
            return -1;
        }
        break;

    case STAIR_DOWN:
        
        if (position->etage + 1 >= position->nbEtageMax){
            position->nbEtageMax++;
        }
        position->etage++;
        position->x = LARGEUR / 2;
        position->y = HAUTEUR / 2;
        return 1;
        break;
    
    default:
        break;
    }
    
    return 0;
}
