/* Auteur : Césaire Agonsè
 * Création: 21-10-21
 * Modification: 05-01-22 */

#include <stdio.h>
#include <stdlib.h>


#include "../include/terrain.h"
#include "../include/perso.h"
#include "../include/inventaire.h"
#include "../include/action.h"
#include "../include/graphique.h"
#include "../include/fichier.h"

SpriteImage sprite;

int main(int argc, char *argv[]){
    
    MLV_Keyboard_button touche;
    Plateau **donjon;
    Perso *perso;
    Position *position;
    Inventaire *invent;
    int direction;
    int *nouvelle_partie, jeu_ouvert;
    Mouse mouse;
    int i;
    
    jeu_ouvert = 0;

    donjon = (Plateau **) malloc(sizeof(Plateau*));
    perso = (Perso *) malloc(sizeof(Perso));
    position = (Position *) malloc(sizeof(Position));
    invent = (Inventaire*) malloc(sizeof(Inventaire));

    nouvelle_partie = (int*) malloc(sizeof(int));

    if (donjon == NULL || perso == NULL || position == NULL || invent == NULL){
        fprintf(stderr, "Erreur d'initialisation mémoire\n");
    }

    *nouvelle_partie = 1;

    srand(time(NULL));
    
    afficherFenetre();
    chargeSprite();

    while(naviguerMenu(nouvelle_partie)){
        jeu_ouvert = 1;
        if(*nouvelle_partie == 1){
            free(donjon);
            donjon = (Plateau **) malloc(sizeof(Plateau*));
            if (donjon == NULL){
                fprintf(stderr, "Erreur d'initialisation mémoire\n");
            }
            donjon[0] = generationEtage(0);

            free(perso);
            perso = (Perso *) malloc(sizeof(Perso));
            if (perso == NULL){
                fprintf(stderr, "Erreur d'initialisation mémoire\n");
            }
            perso = initialisePerso();
            
            free(position);
            position = (Position *) malloc(sizeof(Position));
            if (position == NULL){
                fprintf(stderr, "Erreur d'initialisation mémoire\n");
            }
            position = initialisePosition(LARGEUR / 2, HAUTEUR / 2);

            free(invent);
            invent = (Inventaire*) malloc(sizeof(Inventaire));
            if (invent == NULL){
                fprintf(stderr, "Erreur d'initialisation mémoire\n");
            }
            initialiseInventaire(invent);

            *nouvelle_partie = 2;
        } else if (*nouvelle_partie == 3){
            chargerPerso(perso);
            chargerPosition(position);
            chargerInventaire(invent);
            free(donjon);
            donjon = (Plateau **) malloc(sizeof(Plateau*) * (position->nbEtageMax + 1));
            if (donjon == NULL){
                fprintf(stderr, "Erreur d'initialisation mémoire\n");
            }
            for (i =0; i < (position->nbEtageMax + 1); i++){
                donjon[i] = (Plateau *) malloc(sizeof(Plateau));
                initialiseEtage(donjon[i], i);
                chargerEtage(donjon,i); 
            }
            
            printf("partie chargée\n");
            *nouvelle_partie = 2;
        }
        
        while (touche != MLV_KEYBOARD_ESCAPE && sourisEstSurRetour(mouse) == 0){
            
            afficherPlateau(donjon[position->etage], position);
            
            afficherStat(*perso);
            
            afficherInventaire(*invent);
            
            MLV_actualise_window();
            touche = -1;
            MLV_wait_keyboard_or_mouse(&touche, NULL, NULL, &mouse.x, &mouse.y);
            direction = convertMLVtoDirection(touche);
            
            // un tour de jeu
            if (direction < 4 && direction >= 0){
                if (effectuerTour(donjon, perso, position, invent, direction) != 1){
                    break;
                }
            } else if (touche == 'i' || sourisEstSurInventaire(mouse)){
                utiliserInventaire(perso, invent);
            } else if (touche == 'e' || sourisEstSurAttaque(mouse)){
                if (perso->modeAtk == MAGIC){
                    perso->modeAtk = MELEE;
                } else {
                    perso->modeAtk = MAGIC;
                }
            }

            // Fonction test qui auraient du être fait dans effectuerTour mais
            // le realloc marche seulement dans le main
            if (changeEtage(donjon, position)){
                donjon = (Plateau **) realloc(donjon, sizeof(Plateau *) * (position->nbEtageMax + 1));
            
                if (!rajouteEtage(donjon, position->nbEtageMax)){
                    fprintf(stderr, "Erreur >> dans rajouteEtage, arret du jeu\n");
                    return 0;
                }
            } else if (changeEtage(donjon, position) == -2){
                fprintf(stderr,"Erreur >> dans changeEtage, arret du jeu\n");
                return 0;
            }
        
        }
        
        if (touche == MLV_KEYBOARD_ESCAPE || sourisEstSurRetour(mouse)){
            mouse.x = 0;
            mouse.y = 0;
            touche = 0;
            continue;
        }
        if (!afficherGameOver(nouvelle_partie)){
            break;
        }
    }
    
    MLV_free_window();

    if (jeu_ouvert){
        savePerso(perso);
        printf("sauvegarde du Perso réussie\n");
        savePosition(position);
        printf("sauvegarde de la position réussie\n");
        saveInventaire(invent);
        printf("sauvegarde de l'inventaire réussie\n");
        for (i = 0; i < position->nbEtageMax + 1; i++){
            saveEtage(donjon, i);
            printf("sauvegarde de l'étage %d réussie\n", i);
        }
        printf("sauvegarde du donjon terminé !\n");
    }
    
    free(donjon);
    free(perso);
    free(position);
    free(invent);
    















    /*
    MLV_Keyboard_button touche;
    Plateau **donjon;
    Perso *perso;
    Position *position;
    Inventaire *invent;
    int direction;
    int *nouvelle_partie, jeu_ouvert;
    Mouse mouse;
    int i;
    
    jeu_ouvert = 0;

    donjon = (Plateau **) malloc(sizeof(Plateau*));
    perso = (Perso *) malloc(sizeof(Perso));
    position = (Position *) malloc(sizeof(Position));
    invent = (Inventaire*) malloc(sizeof(Inventaire));

    nouvelle_partie = (int*) malloc(sizeof(int));

    if (donjon == NULL || perso == NULL || position == NULL || invent == NULL){
        fprintf(stderr, "Erreur d'initialisation mémoire\n");
    }

    *nouvelle_partie = 1;

    srand(time(NULL));
    
    afficherFenetre();
    chargeSprite();

    while(naviguerMenu(nouvelle_partie)){
        jeu_ouvert = 1;
        if(*nouvelle_partie == 1){
            free(donjon);
            donjon = (Plateau **) malloc(sizeof(Plateau*));
            if (donjon == NULL){
                fprintf(stderr, "Erreur d'initialisation mémoire\n");
            }
            donjon[0] = generationEtage(0);

            free(perso);
            perso = (Perso *) malloc(sizeof(Perso));
            if (perso == NULL){
                fprintf(stderr, "Erreur d'initialisation mémoire\n");
            }
            perso = initialisePerso();
            
            free(position);
            position = (Position *) malloc(sizeof(Position));
            if (position == NULL){
                fprintf(stderr, "Erreur d'initialisation mémoire\n");
            }
            position = initialisePosition(LARGEUR / 2, HAUTEUR / 2);

            free(invent);
            invent = (Inventaire*) malloc(sizeof(Inventaire));
            if (invent == NULL){
                fprintf(stderr, "Erreur d'initialisation mémoire\n");
            }
            initialiseInventaire(invent);

            *nouvelle_partie = 2;
        } else if (*nouvelle_partie == 3){
            chargerPerso(perso);
            chargerPosition(position);
            chargerInventaire(invent);
            free(donjon);
            donjon = (Plateau **) malloc(sizeof(Plateau*) * (position->nbEtageMax + 1));
            if (donjon == NULL){
                fprintf(stderr, "Erreur d'initialisation mémoire\n");
            }
            for (i =0; i < (position->nbEtageMax + 1); i++){
                donjon[i] = (Plateau *) malloc(sizeof(Plateau));
                initialiseEtage(donjon[i], i);
                chargerEtage(donjon,i); 
            }
            
            printf("partie chargée\n");
            *nouvelle_partie = 2;
        }
        
        while (touche != MLV_KEYBOARD_ESCAPE && sourisEstSurRetour(mouse) == 0){
            
            afficherPlateau(donjon[position->etage], position);
            
            afficherStat(*perso);
            
            afficherInventaire(*invent);
            
            MLV_actualise_window();
            touche = -1;
            MLV_wait_keyboard_or_mouse(&touche, NULL, NULL, &mouse.x, &mouse.y);
            direction = convertMLVtoDirection(touche);
            
            // un tour de jeu
            if (direction < 4 && direction >= 0){
                if (effectuerTour(donjon, perso, position, invent, direction) != 1){
                    break;
                }
            } else if (touche == 'i' || sourisEstSurInventaire(mouse)){
                utiliserInventaire(perso, invent);
            } else if (touche == 'e' || sourisEstSurAttaque(mouse)){
                if (perso->modeAtk == MAGIC){
                    perso->modeAtk = MELEE;
                } else {
                    perso->modeAtk = MAGIC;
                }
            }

            // Fonction test qui auraient du être fait dans effectuerTour mais
            // le realloc marche seulement dans le main
            if (changeEtage(donjon, position)){
                donjon = (Plateau **) realloc(donjon, sizeof(Plateau *) * (position->nbEtageMax + 1));
            
                if (!rajouteEtage(donjon, position->nbEtageMax)){
                    fprintf(stderr, "Erreur >> dans rajouteEtage, arret du jeu\n");
                    return 0;
                }
            } else if (changeEtage(donjon, position) == -2){
                fprintf(stderr,"Erreur >> dans changeEtage, arret du jeu\n");
                return 0;
            }
        
        }
        
        if (touche == MLV_KEYBOARD_ESCAPE || sourisEstSurRetour(mouse)){
            mouse.x = 0;
            mouse.y = 0;
            touche = 0;
            continue;
        }
        if (!afficherGameOver(nouvelle_partie)){
            break;
        }
    }
    
    MLV_free_window();

    if (jeu_ouvert){
        savePerso(perso);
        printf("sauvegarde du Perso réussie\n");
        savePosition(position);
        printf("sauvegarde de la position réussie\n");
        saveInventaire(invent);
        printf("sauvegarde de l'inventaire réussie\n");
        for (i = 0; i < position->nbEtageMax + 1; i++){
            saveEtage(donjon, i);
            printf("sauvegarde de l'étage %d réussie\n", i);
        }
        printf("sauvegarde du donjon terminé !\n");
    }
    
    free(donjon);
    free(perso);
    free(position);
    free(invent);
    */
    return 1;
}