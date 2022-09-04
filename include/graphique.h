/* Auteur : Césaire Agonsè
 * Création: 18-12-21
 * Modification: 05-01-22 */

#ifndef __GRAPHIQUE__
#define __GRAPHIQUE__

#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include <string.h>
#include <assert.h>
#include "../include/terrain.h"
#include "../include/perso.h"
#include "../include/inventaire.h"
#include "../include/position.h"
#include "../include/direction.h"
#include "../include/action.h"

/*taille de la zone de la fenetre*/
#define TAILLE_X 1152
#define TAILLE_Y 648

/*Nombre de case à afficher dans la fenetre*/
#define NB_CASE_X 13
#define NB_CASE_Y 9 

#define TAILLE_CASE TAILLE_Y / NB_CASE_Y

/*Taille arbitraire d'un item dans l'inventaire graphique*/
#define TAILLE_ITEM 50

/*Couleur de l'arrière plan*/
#define BACKGROUND MLV_rgba(34,34,34,255)

typedef struct mouse{
    int x;
    int y;
} Mouse;

typedef struct spriteImage{
    MLV_Image *room;
    MLV_Image *monster_east;
    MLV_Image *monster_north;
    MLV_Image *monster_west;
    MLV_Image *hero_east;
    MLV_Image *hero_north;
    MLV_Image *hero_west;
    MLV_Image *stair;
    MLV_Image *treasure;
    MLV_Image *treasure_open;
    MLV_Image *treasure_open_empty;
    MLV_Image *wall_mid;
    MLV_Image *wall_mid_east;
    MLV_Image *wall_mid_west;
    MLV_Image *wall_mid_east_west;
    MLV_Image *wall_top_corner_north_east;
    MLV_Image *wall_top_corner_north_west;
    MLV_Image *wall_top_corner_south_east;
    MLV_Image *wall_top_corner_south_west;
    MLV_Image *wall_top_east;
    MLV_Image *wall_top_north_east;
    MLV_Image *wall_top_north_mid;
    MLV_Image *wall_top_north_west;
    MLV_Image *wall_top_north_east_west;
    MLV_Image *wall_top_west;
    MLV_Image *ekip_arme;
    MLV_Image *ekip_arme_actif;
    MLV_Image *ekip_baguette;
    MLV_Image *ekip_baguette_actif;
    MLV_Image *ekip_armure;
    MLV_Image *ekip_armure_actif;
    MLV_Image *popo_soin;
    MLV_Image *popo_magie;
    MLV_Image *popo_regen;
    MLV_Image *popo_precision;
    MLV_Image *popo_apprentissage;
    MLV_Image *popo_soin_actif;
    MLV_Image *popo_magie_actif;
    MLV_Image *popo_regen_actif;
    MLV_Image *popo_precision_actif;
    MLV_Image *popo_apprentissage_actif;
    MLV_Image *game_over;
    MLV_Image *menu;
} SpriteImage;

extern SpriteImage sprite;

/*Fonction qui initialise, ouvre la fenetre */
void afficherFenetre();

/*Fonction qui va charger toutes les sprites du jeu dans sprite, la
* variables globales qui contient uniquement des variables de type MLV_Image*/
void chargeSprite();

/*Fonction qui affiche l'image sprite aux coordonées (x,y) dans une grille
de 13*9 cases*/
void afficherCase(MLV_Image *sprite, int x, int y);

/*Fonction qui affiche le hero grâce à afficherCase au centre de la grille*/
void afficherHero(Position *position);

/*Fonction qui affiche un tresor aux coordonées (x,y) grâce à afficherCase dans la fenetre
* selon si il a été fouillé ou non*/
void afficherTresor(Tresor *tresor, int x, int y);

/*Fonction qui affiche un monstre aux coordonées (x,y) grâce à afficherCase dans la fenetre */
void afficherMonstre(Monstre *monstre,  int x, int y);

/*Fonction qui affiche l'étage 13*9 cases autour de la position (x,y) dans la grille du perso */
void afficherPlateau(Plateau *etage, Position *perso);

/*Fonction qui affiche les stats du joueur sur le coté de la fenetre*/
void afficherStat(Perso perso);

/*Fonction qui affiche l'inventaire du joueur sur le coté de la fenetre*/
void afficherInventaire(Inventaire invent);

/*Focntion qui affiche l'image sprite aux coordonées (x,y) dans la
fenetre */
void afficherItem(MLV_Image *sprite,int x, int y);

/*Fonction qui renvoie la direction du bouton touche, renvoie touche elle meme
* si touche n'est pas une direction méridienne*/
int convertMLVtoDirection(MLV_Keyboard_button touche);

/*Fonction qui permet de naviguer dans l'inventaire en appelant afficherInventaire*/
void utiliserInventaire(Perso *perso, Inventaire *invent);

/*Fonction qui affiche l'item en question aux cordonées (x,y) dans la fenetre,
* dans les stat d'equipement si il est actif
* dans l'inventaire sinon */
void afficherItemDansInventaire(Item item, int x, int y, int actif);

/*Fonction qui affiche l'ecran de fin, l'utilisateur doit choisir une option
* pour permettre de relancer une partie ou non
* Renvoie donc l'etat de nouvelle_partie 1 si oui, 0 sinon*/
int afficherGameOver(int *nouvelle_partie);

/*Fonction qui affiche le menu, l'utilisateur doit choisir une option
* pour permettre de lancer une partie ou autre
* Renvoie donc l'etat de nouvelle_partie 1 si oui, 0 pour quitter,
* 2 pour continuer, 3 pour charger une sauvegarde*/
int naviguerMenu(int *nouvelle_partie);

/*Fonction qui affiche uniquement le menu*/
void afficherMenu(int *nouvelle_partie);

/*Fonction qui affiche les crédits et le tuto*/
void afficherCreditTuto();

/*Fonction qui check si la souris est sur le bouton retour (en jeu et inventaire)
*1 si oui, 0 sinon*/
int sourisEstSurRetour(Mouse mouse);

/*Fonction qui check si la souris est n'importe où sur l'inventaire (en jeu)
*1 si oui, 0 sinon*/
int sourisEstSurInventaire(Mouse mouse);

/*Fonction qui check si la souris est sur le bouton mode atk (en jeu)
*1 si oui, 0 sinon*/
int sourisEstSurAttaque(Mouse mouse);

/*Fonction qui check si la souris est sur un item (dans inventaire)
*renvoie le numero de l'item si oui, -1 sinon*/
int sourisEstSurItem(Mouse mouse);

/*Fonction qui check si la souris est sur le bouton jeter (dans inventaire)
*1 si oui, 0 sinon*/
int sourisEstSurJeter(Mouse mouse);

/*Fonction qui check si la souris est sur le bouton jeter (dans inventaire)
*1 si oui, 0 sinon*/
int sourisEstSurJeter(Mouse mouse);

/*Fonction qui check si la souris est sur le bouton jeter (dans inventaire)
*1 si oui, 0 sinon*/
int sourisEstSurEquiper(Mouse mouse);

#endif