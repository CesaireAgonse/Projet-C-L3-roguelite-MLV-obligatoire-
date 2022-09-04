/* Auteur : Césaire Agonsè
 * Création: 21-10-21
 * Modification: 05-01-22 */

#include "../include/terrain.h"

int initialiseEtage(Plateau *plateau, int niveau){
    int i, j;

    plateau->grille = (Cell **) malloc(sizeof(Cell*) * LARGEUR);
    
    if (plateau->grille == NULL){
        return 0;
    }
    
    for (i = 0; i < LARGEUR; i++){
        plateau->grille[i] = (Cell *) malloc(sizeof(Cell) * HAUTEUR);
        
        if (plateau->grille[i] == NULL){
            return 0;
        }
        
        for(j = 0; j < HAUTEUR; j++){
            plateau->grille[i][j].type = WALL;
            plateau->grille[i][j].x = i; /*abscisse*/
            plateau->grille[i][j].y = j; /*ordonnée*/
            plateau->grille[i][j].surCase.monster = NULL;
            plateau->grille[i][j].surCase.tresor = NULL;
        }
    }

    plateau->niveau = niveau;
    return 1;
}

void affichePlateau(Plateau *p){
    int i, j;

    //printf("allo\n");
    for (i = 0; i < HAUTEUR; i++){
        for(j = 0; j < LARGEUR; j++){
            if (p->grille[j][i].type == WALL)
                printf("..");
            else if(p->grille[j][i].type == ROOM)
                printf("[]");
            else if (p->grille[j][i].type == STAIR_DOWN){
                printf("##");
            }
            else if (p->grille[j][i].type == STAIR_UP){
                printf("##");
            }
            else if (p->grille[j][i].type == MONSTER){
                printf("MM");
            }
            else if (p->grille[j][i].type == TREASURE){
                printf("TT");
            }
            
            //printf("%d", p->grille[i][j].type);
            
        }
        printf("\n");
    }
    
}

int distanceManathan(Cell case1, Cell case2){
    return valeurAbsolue(case1.x - case2.x) + valeurAbsolue(case1.y - case2.y);
}

int valeurAbsolue(int nb){
    if (nb < 0){
        return -(nb);
    }
    return nb;
}

ListeCell* alloue_cellule(Cell *case_){
    ListeCell* nouveau;

    nouveau = (ListeCell *) malloc(sizeof(ListeCell));

    if (nouveau == NULL)
        return NULL;

    nouveau->case_  = (Cell *) malloc(sizeof(Cell));
    
    if (nouveau->case_ == NULL)
        return NULL;

    nouveau->case_ = case_;
    
    nouveau->suivante  = (ListeCell *) malloc(sizeof(ListeCell));
    
    if (nouveau->suivante == NULL)
        return NULL;
    
    nouveau->suivante = NULL;

    return nouveau;

}

int ajouterCase(ListeCell *liste, Cell *case_){
    ListeCell *tmp;
    ListeCell *nouveau;

    if (case_ == NULL){
        /*
        printf("erreur case est null dans ajoutercase\n");
        */
        return 0;
    }

    tmp = liste;
    nouveau = alloue_cellule(case_);

    if (nouveau == NULL)
        return 0;

    
    if (liste == NULL) {
        liste = nouveau;
        return 1;
    }

    if (tmp->case_ == NULL){
        tmp->case_ = case_;
        return 1;
    }

    
    while (tmp->suivante != NULL) {
        if (tmp->case_== case_){
            /*
            printf("erreur case est deja la liste\n");
            */
            return 0;
        }
        tmp = tmp->suivante;
    }

    tmp->suivante = nouveau;
    
    return 1;
}

int supprimeCaseListe(ListeCell *liste, Cell *case_){
    ListeCell *tmp;
    ListeCell *suppr;

    assert(case_ != NULL);

    tmp = liste;
    
    if (liste == NULL) {
        /*
        printf("La case n'a pas été trouvée\n");
        */
        return 0;
    }

    
    if (tmp->case_ == case_){
        /*
        printf("La case (%d,%d) a été trouvée et suprimmée 1\n", tmp->case_->x, tmp->case_->y);
        */
        suppr = tmp;
        if (tmp->suivante == NULL){
            /*
            printf("la liste est desormais vide\n");
            */
            free(liste);
            return 0;
        }
        tmp = tmp->suivante;
        liste->case_ = tmp->case_;
        liste->suivante = tmp->suivante;
        free(tmp);
        return 1;
    }
    
    while (tmp->suivante != NULL) {
        

        if (tmp->suivante->case_ == case_){
            /*
            printf("La case (%d,%d) a été trouvée et suprimmée 2\n", tmp->case_->x, tmp->case_->y);
            */
            suppr = tmp->suivante;
            tmp->suivante= suppr->suivante;
            free(suppr);
            return 1;
        }

        tmp = tmp->suivante;
    }
    /*
    printf("La case n'a pas été trouvée\n");
    */
    return 0;
}

void viderListe(ListeCell *liste){
    if (liste->suivante != NULL){
        viderListe(liste->suivante);
    } else {
        free(liste);
    }

    /*
    if (liste != NULL){
        viderListe(liste->suivante);
        free(liste);
        liste = NULL;
    }
    */
}

int afficheListe(ListeCell *liste){
    ListeCell *tmp;
    
    tmp = liste;

    if (liste == NULL) {
        printf("Erreur la liste est vide\n");
        return 0;
    }

    while (tmp->suivante != NULL) {
        if (afficheCase(tmp->case_) == 0){
            return 0;
        }
        tmp = tmp->suivante;
    }
    printf("ici\n");
    if (afficheCase(tmp->case_) == 0){
        return 0;
    }
    return 1;
}

int afficheCase(Cell *case_){
    if (case_ != NULL){
        printf("la case en %d %d est de type ", case_->x, case_->y);
        switch (case_->type)
        {
        case WALL:
            printf("WALL\n");
            break;
        
        case ROOM:
            printf("ROOM\n");
            break;

        case MONSTER:
            printf("MONSTER\n");
            break;

        case TREASURE:
            printf("TREASURE\n");
            break;

        case STAIR_UP:
            printf("STAIR_UP\n");
            break;
        
        case STAIR_DOWN:
            printf("STAIR_DOWN\n");
            break;

        default:
            printf("UKNOWN\n");
            break;
        }
    } else {
        printf("Erreur il y a une case vide\n");
        return 0;
    }
    return 1;
}

Cell* caseAdjacente(Plateau *plateau, Cell *case_, Direction direction, int wall){
    int x , y;

    if (case_ == NULL){
        /*
        printf("erreur case est null dans case Adjacente\n");
        */
        return NULL;
    }

    switch (direction)
    {
    case NORTH:
        y =case_->y - 1;
        x =case_->x;
        if (y == 0 && wall == 0){
            /*
            printf("erreur la case adjacente est un mur\n");
            */
            return NULL;
        }
        if (y < 0){
           return NULL; 
        }
        break;

    case SOUTH:
        y =case_->y + 1;
        x =case_->x;
        if (y == HAUTEUR - 1 && wall == 0){
            /*
            printf("erreur la case adjacente est un mur\n");
            */
            return NULL;
        }
        if (y > HAUTEUR){
           return NULL; 
        }
        break;

    case WEST:
        y =case_->y;
        x =case_->x - 1;
        if (x == 0 && wall == 0){
            /*
            printf("erreur la case adjacente est un mur\n");
            */
            return NULL;
        }
        if (x < 0){
           return NULL; 
        }
        break;

    case EAST:
        y =case_->y;
        x =case_->x + 1;
        if (x == LARGEUR - 1 && wall == 0){
            /*
            printf("erreur la case adjacente est un mur\n");
            */
            return NULL;
        }
        if (x > LARGEUR){
           return NULL; 
        }
        break;

    default:
        return NULL;
        break;
    }
    
    

    return &plateau->grille[x][y];
}

int caseEstAdmissible(Plateau *plateau, Cell *case_){
    ListeCell *analyse1, *analyse2;

    if (case_ == NULL){
        /*
        printf("erreur case est null dans admissible\n");
        */
        return 0;
    }

    analyse1 = alloue_cellule(NULL);
    analyse2 = alloue_cellule(NULL);

    /* on regarde si la case en question est bien un mur*/
    if (case_->type != WALL){
        return 0;
    }

    /* on regarde si il y a bien 1 seule salle sur les cases
    * adjacentes, pour cela on ajoute à la main à une liste
    * toute les cases adjacentes puis on compte le nombre de case
    * de type WALL*/
    
    ajouterCase(analyse1, caseAdjacente(plateau, case_, NORTH, 0));
    ajouterCase(analyse1, caseAdjacente(plateau, case_, EAST, 0));
    ajouterCase(analyse1, caseAdjacente(plateau, case_, WEST, 0));
    ajouterCase(analyse1, caseAdjacente(plateau, case_, SOUTH, 0));

    
    if ((nombreDeCaseListeType(analyse1, ROOM) != 1))
        return 0;
    
    /* meme raisonnement mais a distance 2, pour cela on ajoute dans
    une autre liste les cases adjacentes des cases adjacentes de case_*/
    
    /*on ajoute nord,est,ouest de nord de case*/
    ajouterCase(analyse2, caseAdjacente(plateau, caseAdjacente(plateau, case_, NORTH, 0), NORTH, 0));
    ajouterCase(analyse2, caseAdjacente(plateau, caseAdjacente(plateau, case_, EAST, 0), NORTH, 0));
    ajouterCase(analyse2, caseAdjacente(plateau, caseAdjacente(plateau, case_, WEST, 0), NORTH, 0));
    /*on ajoute sud,est,ouest de sud de case*/
    ajouterCase(analyse2, caseAdjacente(plateau, caseAdjacente(plateau, case_, SOUTH, 0), SOUTH, 0));
    ajouterCase(analyse2, caseAdjacente(plateau, caseAdjacente(plateau, case_, EAST, 0), SOUTH, 0));
    ajouterCase(analyse2, caseAdjacente(plateau, caseAdjacente(plateau, case_, WEST, 0), SOUTH, 0));
    /*on ajoute est de est de case*/
    ajouterCase(analyse2, caseAdjacente(plateau, caseAdjacente(plateau, case_, EAST, 0), EAST, 0));
    /*on ajoute ouest de ouest de case*/
    ajouterCase(analyse2, caseAdjacente(plateau, caseAdjacente(plateau, case_, WEST, 0), WEST, 0));
    
    if (nombreDeCaseListeType(analyse2, ROOM) > 2)
        return 0;

    /*vider liste*/
    
    return 1;
}

int nombreDeCaseListeType(ListeCell *liste, int type){
    ListeCell *tmp;
    int nb_type;

    nb_type = 0;
    tmp = liste;

    if (liste == NULL) {
        return 0;
    }

    while (tmp->suivante != NULL) {
        assert(tmp->case_ != NULL);

        if (tmp->case_->type == type){
            nb_type += 1;
        }
        tmp = tmp->suivante;
    }
    assert(tmp->case_ != NULL);

    if (tmp->case_->type == type){
        nb_type += 1;
    }

    return nb_type;
}

int nombreDeCaseListe(ListeCell *liste){
    ListeCell *tmp;
    int nb_case;

    nb_case = 1;
    tmp = liste;

    if (liste == NULL) {
        return 0;
    }

    while (tmp->suivante != NULL) {
        assert(tmp->case_ != NULL);
        nb_case += 1;
        tmp = tmp->suivante;
    }
    assert(tmp->case_ != NULL);
    /*nb_case += 1;*/
    
    return nb_case;
}

Cell* trouverCaseNum(ListeCell *liste, int num){
    ListeCell *tmp;
    int nb_case;

    nb_case = 1;
    tmp = liste;

    if (liste == NULL) {
        return 0;
    }

    while (tmp->suivante != NULL) {
        assert(tmp->case_ != NULL);
        if (nb_case == num){
            return tmp->case_;
        }
        
        nb_case += 1;
        tmp = tmp->suivante;
    }
    assert(tmp->case_ != NULL);
    if (nb_case == num){
        return tmp->case_;
    }
    printf("je retourne null %d\n", num);
    return NULL;
}

Plateau* generationEtage(int niveau){
    Plateau *p;
    int nb_monstre;
    int securite_mauvais_alea;
    Cell *centre, *case_sujet, *tresor;
    ListeCell *analyse;
    p = (Plateau *) malloc(sizeof(Plateau));
    if (p == NULL){
        fprintf(stderr, "Erreur d'initialisation mémoire\n");
    }
    p->niveau = niveau;
    
    securite_mauvais_alea = -1;
    centre = (Cell *) malloc(sizeof(Cell));
    case_sujet = (Cell *) malloc(sizeof(Cell));
    
    centre->x = LARGEUR / 2;
    centre->y = HAUTEUR / 2;

    case_sujet->x = LARGEUR / 2;
    case_sujet->y = HAUTEUR / 2;
    case_sujet->type = WALL;
    if (!initialiseEtage(p, niveau))
        return p;
    
    do {
        if (securite_mauvais_alea > 500 || securite_mauvais_alea < 0){
            
            /*generation du labyrinthe*/
            generationLabyrinthe(p, p->grille[centre->x][centre->y]);
            /*generation des escalier montant*/
            p->grille[centre->x][centre->y].type = STAIR_UP;
            
            securite_mauvais_alea = 0;
            continue;
        } else {
            securite_mauvais_alea++;
        }


        do {
            if (securite_mauvais_alea > 500){
                break;
            } else {
                securite_mauvais_alea++;
            }
            
            if (rand() % 2 == 1)
                case_sujet->x = LARGEUR - 2;
            else 
                case_sujet->x = 1;

            if (rand() % 2 == 1)
                case_sujet->y = HAUTEUR - 2;
            else 
                case_sujet->y = 1;
            
        }
        while (p->grille[case_sujet->x][case_sujet->y].type != ROOM);
        
        
    /*generation des descendant*/    
    /*l'escalier descendent est à distance 50 car sinon au dessus ce n'est pas possible*/
    } while (distanceManathan(*centre, *case_sujet) < 50);
    
    p->grille[case_sujet->x][case_sujet->y].type = STAIR_DOWN;
    
    /*Generation du coffre bonus*/
    if (niveau == 0){
        do {
            tresor = caseAdjacente(p, centre, rand() % 4, 0);
        } while (p->grille[tresor->x][tresor->y].type != ROOM);
    
    
    p->grille[tresor->x][tresor->y].type = TREASURE;
    p->grille[tresor->x][tresor->y].surCase.tresor = initialiseTresor(niveau, ALEA);
    }

    /*Generation des monstres*/    
    for (nb_monstre = 0; nb_monstre < 10; nb_monstre++){
        securite_mauvais_alea = 0;
        do{
            analyse = alloue_cellule(NULL);
            
            do {
                if (securite_mauvais_alea > 500){
                    break;
                }
                securite_mauvais_alea++;
                case_sujet->x = rand() % LARGEUR;
                case_sujet->y = rand() % HAUTEUR;
                
            }
            while (p->grille[case_sujet->x][case_sujet->y].type != ROOM);
            
            if (securite_mauvais_alea > 500){
                /*
                viderListe(analyse);
                */
                break;
            }

            ajouterCase(analyse, caseAdjacente(p, case_sujet, NORTH, 1));
            ajouterCase(analyse, caseAdjacente(p, case_sujet, EAST, 1));
            ajouterCase(analyse, caseAdjacente(p, case_sujet, WEST, 1));
            ajouterCase(analyse, caseAdjacente(p, case_sujet, SOUTH, 1));
            
        /*Le monstre est placé dans un couloir ou au fond d'un couloir*/
        }while(((nombreDeCaseListeType(analyse, ROOM) != 1) || (nombreDeCaseListeType(analyse, WALL) != 3)) && ((nombreDeCaseListeType(analyse, ROOM) != 2) || (nombreDeCaseListeType(analyse, WALL) != 2)));

        p->grille[case_sujet->x][case_sujet->y].type = MONSTER;
        p->grille[case_sujet->x][case_sujet->y].surCase.monster = initialiseMonstre(niveau);

    }

    return p;
}

int generationLabyrinthe(Plateau *plateau, Cell case_){
    ListeCell *toexpand, *analyse;
    Cell *case_c;
    int nb_case, indice;
    int i, j;
    
    nb_case = 0;
    toexpand = alloue_cellule(NULL);
    plateau->grille[case_.x][case_.y].type = ROOM;
    /*Etape 1*/
    ajouterCase(toexpand, caseAdjacente(plateau, &case_, NORTH, 0));
    ajouterCase(toexpand, caseAdjacente(plateau, &case_, SOUTH, 0));
    ajouterCase(toexpand, caseAdjacente(plateau, &case_, EAST, 0));
    ajouterCase(toexpand, caseAdjacente(plateau, &case_, WEST, 0));

    
    
    do{
        do{
            /*Etape 2 retirer aléatoirement une case c de la liste*/
            /*
            afficheListe(toexpand);
            
            printf("---\n");
            */
            if (toexpand->case_ == NULL){
                /*
                printf("il faudrait sortir\n");
                */
                break;
            }
            //printf("on rentre %d\n", nb_case);
            nb_case = nombreDeCaseListe(toexpand);
            indice = rand() % nb_case + 1;
            case_c = trouverCaseNum(toexpand, indice);
            
            supprimeCaseListe(toexpand, case_c);
            
            if (toexpand->case_ == NULL){
                /*
                printf("il faudrait sortir\n");
                */
                break;
            }
            
        /*Etape 3 Si case_c n’est pas admissible, revenir à l’étape 2,
        * sinon convertir c en une case de salle et passer à l’étape 4 */
        
        }while (!caseEstAdmissible(plateau, case_c));

        
        if (toexpand->case_ == NULL && !caseEstAdmissible(plateau, case_c)){
            /*
            printf("il faudrait vraiment sortir\n");
            */
            break;
        }
        

        case_c->type = ROOM;
        /*
        printf("on ajoute la case (%d,%d)\n", case_c->x, case_c->y);
        affichePlateau(plateau);
        */
       
        /*Etape 4 regarder les 4 cases adjacentes à case_c et ajouter
        * celles qui sont admissible*/
        
        if (caseEstAdmissible(plateau, caseAdjacente(plateau, case_c, NORTH, 0))){
            ajouterCase(toexpand, caseAdjacente(plateau, case_c, NORTH, 0));
        }
        
        if (caseEstAdmissible(plateau, caseAdjacente(plateau, case_c, SOUTH, 0))){
            ajouterCase(toexpand, caseAdjacente(plateau, case_c, SOUTH, 0));
        }
        
        if (caseEstAdmissible(plateau, caseAdjacente(plateau, case_c, EAST, 0)) ){
            ajouterCase(toexpand, caseAdjacente(plateau, case_c, EAST, 0));
        }
        
        if (caseEstAdmissible(plateau, caseAdjacente(plateau, case_c, WEST, 0))){
            ajouterCase(toexpand, caseAdjacente(plateau, case_c, WEST, 0));
        }
        
        /*Etape 5 Tant que to expand n'est pas vide revenir à l'etape 2*/
    }
    while (toexpand->case_ != NULL);

    viderListe(toexpand);
    /*Etape 6 Identifier tous les cases de salle adjacentes à
    * trois cases de mur. Passer ces cases en cases de
    * mur, puis terminer.*/
    
    
    for (i = 0; i < LARGEUR; i++){
        for(j = 0; j < HAUTEUR; j++){
            /*On sécurise les coins*/
            if ((i == 1 && j == 1) || (i == LARGEUR - 2 && j == 1) || (i == 1 && j == HAUTEUR - 2) || (i == LARGEUR - 2 && j == HAUTEUR - 2)){
                continue;
            }
                

            if (plateau->grille[i][j].type == ROOM ){
                /*
                printf("ALLO ? (%d,%d)\n",plateau->grille[i][j].x, plateau->grille[i][j].y);
                */
                analyse = alloue_cellule(NULL);
                case_c = &plateau->grille[i][j];
                ajouterCase(analyse, caseAdjacente(plateau, case_c, NORTH, 1));
                ajouterCase(analyse, caseAdjacente(plateau, case_c, EAST, 1));
                ajouterCase(analyse, caseAdjacente(plateau, case_c, WEST, 1));
                ajouterCase(analyse, caseAdjacente(plateau, case_c, SOUTH, 1));

                
                if ((nombreDeCaseListeType(analyse, WALL) == 3)){
                    /*
                    printf("j'enleve la case (%d,%d)\n",plateau->grille[i][j].x, plateau->grille[i][j].y );
                    */
                    plateau->grille[i][j].type = WALL;
                }
                    

            }
            
        }
    }
    /*
    viderListe(analyse);
    */
    
    return 1;
}

int rajouteEtage(Plateau **plateau, int nbEtageMax){

    if (nbEtageMax < 0){
        fprintf(stderr, "Erreur >> Parametre invalide dans rajouteEtage\n");
        return 0;
    }else if (plateau == NULL){
        fprintf(stderr, "Erreur >> L'adresse du donjon est nulle\n");
        return 0;
    } else if (&plateau[nbEtageMax] == NULL){
        fprintf(stderr, "Erreur >> L'adresse de l'etage du donjon est nulle\n");
        return 0;
    }
    /*Le realloc est fait en dehors de la fonction car cela ne fait pas effet dans le cas
    contraire et je n'ai pas trouvé pourquoi*/
    /*plateau = (Plateau **) realloc(plateau, sizeof(Plateau *) * (nbEtageMax + 1));*/

    if (plateau == NULL){
        fprintf(stderr, "Erreur >> Probleme de réallocation mémoire dans rajouteEtage\n");
        return 0;
    }

    plateau[nbEtageMax] = generationEtage(nbEtageMax);

    if (plateau[nbEtageMax] == NULL){
        fprintf(stderr, "Erreur >> Probleme d'allocation mémoire dans rajouteEtage\n");
        return 0;
    }
    return 1;
}
