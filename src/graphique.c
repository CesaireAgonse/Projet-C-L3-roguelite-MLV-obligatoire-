/* Auteur : Césaire Agonsè
 * Création: 18-12-21
 * Modification: 05-01-22 */

#include "../include/graphique.h"

void afficherFenetre(){
    MLV_create_window("Donjon" , "Donjon", TAILLE_X, TAILLE_Y);
    MLV_clear_window(BACKGROUND);
}

void afficherCase(MLV_Image *sprite, int x, int y){
    
    MLV_draw_image(sprite, TAILLE_CASE * x, TAILLE_CASE * y);
    
}

void afficherPlateau(Plateau *plateau, Position *perso){
    MLV_Font *font;
    int x_min, y_min;
    int i, j;
    assert(perso->x >= 1);
    assert(perso->y >= 1);
    assert(perso->x < LARGEUR);
    assert(perso->y < HAUTEUR);

    

    x_min = perso->x - 6;
    y_min = perso->y - 4;

    MLV_draw_filled_rectangle(0, 0, TAILLE_CASE * NB_CASE_X, TAILLE_Y, BACKGROUND);

    for (i = 0; i < NB_CASE_X ; i++){
        for (j = 0; j < NB_CASE_Y ; j++){
            
            if (x_min + i >= 0 && x_min + i < LARGEUR && y_min + j >= 0 && y_min + j < HAUTEUR){
                /*Cas des bordures sinon il y a une erreur*/
                if ((x_min + i) < 1){
                    /*Cas des mur sur le coté ouest*/
                    if ((x_min + i) == 0){
                        if (plateau->grille[x_min + i + 1][y_min + j].type !=  WALL && plateau->grille[x_min + i][y_min + j + 1].type ==  WALL){
                            if (plateau->grille[x_min + i + 1][y_min + j + 1].type ==  WALL){
                                afficherCase(sprite.wall_top_corner_south_east, i, j);
                            }  else {
                                afficherCase(sprite.wall_top_east, i, j);
                            }
                        } else if (plateau->grille[x_min + i + 1][y_min + j].type ==  WALL && plateau->grille[x_min + i][y_min + j + 1].type ==  WALL && plateau->grille[x_min + i + 1][y_min + j + 1].type !=  WALL){
                            afficherCase(sprite.wall_top_corner_north_east, i, j);
                        }
                    }
                    
                    continue;
                }else if ((y_min + j) < 1){
                    if ((x_min + i) < LARGEUR - 1){
                        /*Cas des mur sur le coté nord*/
                        if (plateau->grille[x_min + i][y_min + j + 1].type !=  WALL){
                            if (plateau->grille[x_min + i + 1][y_min + j].type !=  WALL && plateau->grille[x_min + i - 1][y_min + j].type !=  WALL){
                                afficherCase(sprite.wall_mid_east_west, i, j);
                            } else if (plateau->grille[x_min + i + 1][y_min + j].type !=  WALL){
                                afficherCase(sprite.wall_mid_east, i, j);
                            } else if (plateau->grille[x_min + i - 1][y_min + j].type !=  WALL){
                                afficherCase(sprite.wall_mid_west, i, j);
                            } else {
                                afficherCase(sprite.wall_mid, i, j);
                            }
                        }

                        /*Cas des mur sur le coté ouest*/
                        if (plateau->grille[x_min + i + 1][y_min + j].type !=  WALL && plateau->grille[x_min + i][y_min + j + 1].type ==  WALL){
                            if (plateau->grille[x_min + i + 1][y_min + j + 1].type ==  WALL){
                                afficherCase(sprite.wall_top_corner_south_east, i, j);
                            }  else {
                                afficherCase(sprite.wall_top_east, i, j);
                            }
                        } else if (plateau->grille[x_min + i + 1][y_min + j].type ==  WALL && plateau->grille[x_min + i][y_min + j + 1].type ==  WALL && plateau->grille[x_min + i + 1][y_min + j + 1].type !=  WALL){
                            afficherCase(sprite.wall_top_corner_north_east, i, j);
                        }
                    }
                    
                    /*Cas des mur sur le coté est*/
                    if (plateau->grille[x_min + i - 1][y_min + j].type !=  WALL && plateau->grille[x_min + i][y_min + j + 1].type ==  WALL){
                        if (plateau->grille[x_min + i - 1][y_min + j + 1].type ==  WALL){
                            afficherCase(sprite.wall_top_corner_south_west, i, j);
                        }  else {
                            afficherCase(sprite.wall_top_west, i, j);
                        }
                    } else if (plateau->grille[x_min + i - 1][y_min + j].type ==  WALL && plateau->grille[x_min + i][y_min + j + 1].type ==  WALL && plateau->grille[x_min + i - 1][y_min + j + 1].type !=  WALL){
                        afficherCase(sprite.wall_top_corner_north_west, i, j);
                    }

                    continue;
                } else if ((x_min + i) >= LARGEUR - 1){
                    /*Cas des mur sur le coté est*/
                    if (plateau->grille[x_min + i - 1][y_min + j].type !=  WALL && plateau->grille[x_min + i][y_min + j + 1].type ==  WALL){
                        if (plateau->grille[x_min + i - 1][y_min + j + 1].type ==  WALL){
                            afficherCase(sprite.wall_top_corner_south_west, i, j);
                        }  else {
                            afficherCase(sprite.wall_top_west, i, j);
                        }
                    } else if (plateau->grille[x_min + i - 1][y_min + j].type ==  WALL && plateau->grille[x_min + i][y_min + j + 1].type ==  WALL && plateau->grille[x_min + i - 1][y_min + j + 1].type !=  WALL){
                        afficherCase(sprite.wall_top_corner_north_west, i, j);
                    }
                    continue;
                } else if ((y_min + j) >= HAUTEUR - 1){
                    continue;
                }
                
                /*Cas des cases de salles*/
                if (plateau->grille[x_min + i][y_min + j].type !=  WALL){
                    afficherCase(sprite.room, i, j);
                    if (plateau->grille[x_min + i][y_min + j].type == TREASURE){
                        afficherTresor(plateau->grille[x_min + i][y_min + j].surCase.tresor, i, j);
                        
                    }
                    if (plateau->grille[x_min + i][y_min + j].type == MONSTER){
                        afficherMonstre(plateau->grille[x_min + i][y_min + j].surCase.monster, i, j);
                    }
                    if (plateau->grille[x_min + i][y_min + j].type == STAIR_DOWN || plateau->grille[x_min + i][y_min + j].type == STAIR_UP){
                       afficherCase(sprite.stair, i, j); 
                    }
                    if (x_min + i == perso->x && y_min + j == perso->y){
                       afficherHero(perso); 
                    }
                    /*Si il y a un mur en dessous de la case*/
                    if (plateau->grille[x_min + i][y_min + j + 1].type ==  WALL){
                        if (plateau->grille[x_min + i + 1][y_min + j + 1].type !=  WALL && plateau->grille[x_min + i - 1][y_min + j + 1].type !=  WALL){
                            afficherCase(sprite.wall_top_north_east_west, i, j);
                        }else if (plateau->grille[x_min + i + 1][y_min + j + 1].type !=  WALL){
                            afficherCase(sprite.wall_top_north_east, i, j);
                        } else if (plateau->grille[x_min + i - 1][y_min + j + 1].type !=  WALL){
                            afficherCase(sprite.wall_top_north_west, i, j);
                        } else {
                            afficherCase(sprite.wall_top_north_mid, i, j);
                        }
                    }
                
                } 
                /*Tout les cas possibles pour les murs*/
                else {
                    /*Cas des mur sur le coté ouest*/
                    if (plateau->grille[x_min + i + 1][y_min + j].type !=  WALL && plateau->grille[x_min + i][y_min + j + 1].type ==  WALL){
                        if (plateau->grille[x_min + i + 1][y_min + j + 1].type ==  WALL){
                            afficherCase(sprite.wall_top_corner_south_east, i, j);
                        }  else {
                            afficherCase(sprite.wall_top_east, i, j);
                        }
                    } else if (plateau->grille[x_min + i + 1][y_min + j].type ==  WALL && plateau->grille[x_min + i][y_min + j + 1].type ==  WALL && plateau->grille[x_min + i + 1][y_min + j + 1].type !=  WALL){
                        afficherCase(sprite.wall_top_corner_north_east, i, j);
                    }
                    /*Cas des mur sur le coté est*/
                    if (plateau->grille[x_min + i - 1][y_min + j].type !=  WALL && plateau->grille[x_min + i][y_min + j + 1].type ==  WALL){
                        if (plateau->grille[x_min + i - 1][y_min + j + 1].type ==  WALL){
                            afficherCase(sprite.wall_top_corner_south_west, i, j);
                        }  else {
                            afficherCase(sprite.wall_top_west, i, j);
                        }
                    } else if (plateau->grille[x_min + i - 1][y_min + j].type ==  WALL && plateau->grille[x_min + i][y_min + j + 1].type ==  WALL && plateau->grille[x_min + i - 1][y_min + j + 1].type !=  WALL){
                        afficherCase(sprite.wall_top_corner_north_west, i, j);
                    }
                    /*Cas des mur sur le coté nord*/
                    if (plateau->grille[x_min + i][y_min + j + 1].type !=  WALL){
                        if (plateau->grille[x_min + i + 1][y_min + j].type !=  WALL && plateau->grille[x_min + i - 1][y_min + j].type !=  WALL){
                            afficherCase(sprite.wall_mid_east_west, i, j);
                        } else if (plateau->grille[x_min + i + 1][y_min + j].type !=  WALL){
                            afficherCase(sprite.wall_mid_east, i, j);
                        } else if (plateau->grille[x_min + i - 1][y_min + j].type !=  WALL){
                            afficherCase(sprite.wall_mid_west, i, j);
                        } else {
                            afficherCase(sprite.wall_mid, i, j);
                        }
                    }
                    
                }
                
            }
        }
    }

    font = MLV_load_font("sprite/Pixeloid.ttf", 30);
    MLV_draw_text_with_font(0, TAILLE_Y - 30, "Level %d", font, MLV_COLOR_WHITE, plateau->niveau);

    MLV_draw_filled_rectangle(TAILLE_CASE * NB_CASE_X - 110, TAILLE_Y - 50, 100, 45, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(TAILLE_CASE * NB_CASE_X - 105, TAILLE_Y - 45, 90, 35, BACKGROUND);
    MLV_draw_text_with_font(TAILLE_CASE * NB_CASE_X - 100, TAILLE_Y - 45, "Back", font, MLV_COLOR_WHITE);

    if (plateau->grille[1][1].type == STAIR_DOWN){
       MLV_draw_text_with_font(TAILLE_CASE * NB_CASE_X - 500, TAILLE_Y - 45, "HAUT GAUCHE", font, MLV_COLOR_WHITE); 
    } else if (plateau->grille[1][HAUTEUR - 2].type == STAIR_DOWN) {
        MLV_draw_text_with_font(TAILLE_CASE * NB_CASE_X - 500, TAILLE_Y - 45, "BAS GAUCHE", font, MLV_COLOR_WHITE); 
    } else if (plateau->grille[LARGEUR - 2][HAUTEUR - 2].type == STAIR_DOWN) {
        MLV_draw_text_with_font(TAILLE_CASE * NB_CASE_X - 500, TAILLE_Y - 45, "BAS DROITE", font, MLV_COLOR_WHITE); 
    } else if (plateau->grille[LARGEUR - 2][1].type == STAIR_DOWN) {
        MLV_draw_text_with_font(TAILLE_CASE * NB_CASE_X - 500, TAILLE_Y - 45, "HAUT DROITE", font, MLV_COLOR_WHITE); 
    }

    MLV_free_font(font);
}

void chargeSprite(){
    sprite.room = MLV_load_image("sprite/src/ROOM.png");
    MLV_resize_image(sprite.room, TAILLE_CASE, TAILLE_CASE);

    sprite.monster_east = MLV_load_image("sprite/src/MONSTER_EAST.png");
    MLV_resize_image(sprite.monster_east, TAILLE_CASE, TAILLE_CASE);

    sprite.monster_north = MLV_load_image("sprite/src/MONSTER_NORTH.png");
    MLV_resize_image(sprite.monster_north, TAILLE_CASE, TAILLE_CASE);

    sprite.monster_west = MLV_load_image("sprite/src/MONSTER_EAST.png");
    MLV_resize_image(sprite.monster_west, TAILLE_CASE, TAILLE_CASE);

    sprite.hero_east = MLV_load_image("sprite/src/HERO_EAST.png");
    MLV_resize_image(sprite.hero_east, TAILLE_CASE, TAILLE_CASE);

    sprite.hero_north = MLV_load_image("sprite/src/HERO_NORTH.png");
    MLV_resize_image(sprite.hero_north, TAILLE_CASE, TAILLE_CASE);

    sprite.hero_west = MLV_load_image("sprite/src/HERO_WEST.png");
    MLV_resize_image(sprite.hero_west, TAILLE_CASE, TAILLE_CASE);

    sprite.wall_mid = MLV_load_image("sprite/src/WALL_MID.png");
    MLV_resize_image(sprite.wall_mid, TAILLE_CASE, TAILLE_CASE);

    sprite.wall_mid_east = MLV_load_image("sprite/src/WALL_MID_EAST.png");
    MLV_resize_image(sprite.wall_mid_east, TAILLE_CASE, TAILLE_CASE);

    sprite.wall_mid_west = MLV_load_image("sprite/src/WALL_MID_WEST.png");
    MLV_resize_image(sprite.wall_mid_west, TAILLE_CASE, TAILLE_CASE);

    sprite.wall_mid_east_west = MLV_load_image("sprite/src/WALL_MID_EAST_WEST.png");
    MLV_resize_image(sprite.wall_mid_east_west, TAILLE_CASE, TAILLE_CASE);

    sprite.wall_top_east = MLV_load_image("sprite/src/WALL_TOP_EAST.png");
    MLV_resize_image(sprite.wall_top_east, TAILLE_CASE, TAILLE_CASE);

    sprite.wall_top_west = MLV_load_image("sprite/src/WALL_TOP_WEST.png");
    MLV_resize_image(sprite.wall_top_west, TAILLE_CASE, TAILLE_CASE);

    sprite.wall_top_north_east_west = MLV_load_image("sprite/src/WALL_TOP_NORTH_EAST_WEST.png");
    MLV_resize_image(sprite.wall_top_north_east_west, TAILLE_CASE, TAILLE_CASE);

    sprite.wall_top_north_east = MLV_load_image("sprite/src/WALL_TOP_NORTH_EAST.png");
    MLV_resize_image(sprite.wall_top_north_east, TAILLE_CASE, TAILLE_CASE);

    sprite.wall_top_north_mid = MLV_load_image("sprite/src/WALL_TOP_NORTH_MID.png");
    MLV_resize_image(sprite.wall_top_north_mid, TAILLE_CASE, TAILLE_CASE);

    sprite.wall_top_north_west = MLV_load_image("sprite/src/WALL_TOP_NORTH_WEST.png");
    MLV_resize_image(sprite.wall_top_north_west, TAILLE_CASE, TAILLE_CASE);

    sprite.wall_top_corner_north_east = MLV_load_image("sprite/src/WALL_TOP_CORNER_NORTH_EAST.png");
    MLV_resize_image(sprite.wall_top_corner_north_east, TAILLE_CASE, TAILLE_CASE);

    sprite.wall_top_corner_north_west = MLV_load_image("sprite/src/WALL_TOP_CORNER_NORTH_WEST.png");
    MLV_resize_image(sprite.wall_top_corner_north_west, TAILLE_CASE, TAILLE_CASE);

    sprite.wall_top_corner_south_east = MLV_load_image("sprite/src/WALL_TOP_CORNER_SOUTH_EAST.png");
    MLV_resize_image(sprite.wall_top_corner_south_east, TAILLE_CASE, TAILLE_CASE);

    sprite.wall_top_corner_south_west = MLV_load_image("sprite/src/WALL_TOP_CORNER_SOUTH_WEST.png");
    MLV_resize_image(sprite.wall_top_corner_south_west, TAILLE_CASE, TAILLE_CASE);

    sprite.stair = MLV_load_image("sprite/src/STAIR.png");
    MLV_resize_image(sprite.stair, TAILLE_CASE, TAILLE_CASE);

    sprite.treasure = MLV_load_image("sprite/src/TREASURE_CLOSE.png");
    MLV_resize_image(sprite.treasure, TAILLE_CASE, TAILLE_CASE);

    sprite.treasure_open = MLV_load_image("sprite/src/TREASURE_OPEN.png");
    MLV_resize_image(sprite.treasure_open, TAILLE_CASE, TAILLE_CASE);

    sprite.treasure_open_empty = MLV_load_image("sprite/src/TREASURE_OPEN_EMPTY.png");
    MLV_resize_image(sprite.treasure_open_empty, TAILLE_CASE, TAILLE_CASE);

    sprite.ekip_arme = MLV_load_image("sprite/src/EKIP_ARME.png");
    MLV_resize_image(sprite.ekip_arme, TAILLE_ITEM, TAILLE_ITEM);
    sprite.ekip_arme_actif = MLV_load_image("sprite/src/EKIP_ARME.png");
    MLV_resize_image(sprite.ekip_arme_actif, 40, 40);

    sprite.ekip_armure = MLV_load_image("sprite/src/EKIP_ARMURE.png");
    MLV_resize_image(sprite.ekip_armure, TAILLE_ITEM, TAILLE_ITEM);
    sprite.ekip_armure_actif = MLV_load_image("sprite/src/EKIP_ARMURE.png");
    MLV_resize_image(sprite.ekip_armure_actif, 40, 40);
    
    sprite.ekip_baguette = MLV_load_image("sprite/src/EKIP_BAGUETTE.png");
    MLV_resize_image(sprite.ekip_baguette, TAILLE_ITEM, TAILLE_ITEM);
    sprite.ekip_baguette_actif = MLV_load_image("sprite/src/EKIP_BAGUETTE.png");
    MLV_resize_image(sprite.ekip_baguette_actif, 40, 40);

    sprite.popo_soin = MLV_load_image("sprite/src/POPO_SOIN.png");
    MLV_resize_image(sprite.popo_soin, TAILLE_ITEM, TAILLE_ITEM);
    sprite.popo_soin_actif = MLV_load_image("sprite/src/POPO_SOIN.png");
    MLV_resize_image(sprite.popo_soin_actif, 40, 40);

    sprite.popo_magie = MLV_load_image("sprite/src/POPO_MAGIE.png");
    MLV_resize_image(sprite.popo_magie, TAILLE_ITEM, TAILLE_ITEM);
    sprite.popo_magie_actif = MLV_load_image("sprite/src/POPO_MAGIE.png");
    MLV_resize_image(sprite.popo_magie_actif, 40, 40);

    sprite.popo_regen = MLV_load_image("sprite/src/POPO_REGEN.png");
    MLV_resize_image(sprite.popo_regen, TAILLE_ITEM, TAILLE_ITEM);
    sprite.popo_regen_actif = MLV_load_image("sprite/src/POPO_REGEN.png");
    MLV_resize_image(sprite.popo_regen_actif, 40, 40);

    sprite.popo_precision = MLV_load_image("sprite/src/POPO_PRECISION.png");
    MLV_resize_image(sprite.popo_precision, TAILLE_ITEM, TAILLE_ITEM);
    sprite.popo_precision_actif = MLV_load_image("sprite/src/POPO_PRECISION.png");
    MLV_resize_image(sprite.popo_precision_actif, 40, 40);

    sprite.popo_apprentissage = MLV_load_image("sprite/src/POPO_APPRENTISSAGE.png");
    MLV_resize_image(sprite.popo_apprentissage, TAILLE_ITEM, TAILLE_ITEM);
    sprite.popo_apprentissage_actif = MLV_load_image("sprite/src/POPO_APPRENTISSAGE.png");
    MLV_resize_image(sprite.popo_apprentissage_actif, 40, 40);

    sprite.game_over = MLV_load_image("sprite/src/GAME_OVER.png");
    MLV_resize_image(sprite.game_over, 760, 440);

    sprite.menu = MLV_load_image("sprite/src/MENU.png");
    MLV_resize_image(sprite.menu, 760, 440);
    
}

void afficherStat(Perso perso){
    MLV_Font *font;
    MLV_Font *stat;
    int o;

    o = TAILLE_CASE * NB_CASE_X;
    font = MLV_load_font("sprite/Pixeloid.ttf", 30);
    stat = MLV_load_font("sprite/Pixeloid.ttf", 20);
    

    MLV_draw_filled_rectangle(o, 0, TAILLE_X - o, 345, MLV_COLOR_BLACK);

    MLV_draw_text_with_font(o + 10, 20, "HP", font, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(o + 85, 20, 110, 35, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(o + 90, 25, 100, 25,MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle(o + 90, 25, perso.hp * 100 / (perso.def * 10), 25,MLV_COLOR_RED);
    MLV_draw_text_with_font(o + 95, 25, "%d/%d", stat, MLV_COLOR_WHITE, perso.hp, perso.def * 10);
    
    
    MLV_draw_text_with_font(o + 10, 60, "MP", font, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(o + 85, 60, 110, 35, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(o + 90, 65, 100, 25, MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle(o + 90, 65, perso.mp * 100 / (perso.inte * 10 - 50), 25, MLV_COLOR_BLUE);
    MLV_draw_text_with_font(o + 95, 65, "%d/%d", stat, MLV_COLOR_WHITE, perso.mp, perso.inte * 10 - 50);
    
    
    MLV_draw_text_with_font(o + 10, 100, "EXP", font, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(o + 85, 100, 110, 35, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(o + 90, 105, 100, 25, MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle(o + 90, 105, perso.exp * 100 / ((perso.lv * 50) + 350), 25, MLV_COLOR_GREEN3);
    MLV_draw_text_with_font(o + 95, 105, "%d/%d", stat, MLV_COLOR_WHITE, perso.exp, (perso.lv * 50) + 350);

    MLV_draw_text_with_font(o + 10, 140, "Atk", font, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(o + 95, 150, "%d", stat, MLV_COLOR_WHITE, perso.atk);
    if (perso.arme->type != VIDE){
        afficherItemDansInventaire(*perso.arme, o  + 125, 140, 1);
    }

    MLV_draw_text_with_font(o + 10, 180, "Def", font, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(o + 95, 190, "%d", stat, MLV_COLOR_WHITE, perso.def);
    if (perso.armure->type != VIDE){
        afficherItemDansInventaire(*perso.armure, o  + 125, 180, 1);
    }

    MLV_draw_text_with_font(o + 10, 220, "Int", font, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(o + 95, 230, "%d", stat, MLV_COLOR_WHITE, perso.inte);
    if (perso.baguette->type != VIDE){
        afficherItemDansInventaire(*perso.baguette, o  + 125, 220, 1);
    }
    
    MLV_draw_text_with_font(o + 10, 260, "Lvl", font, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(o + 95, 270, "%d", stat, MLV_COLOR_WHITE, perso.lv);
    if (perso.popo->type != VIDE){
        afficherItemDansInventaire(*perso.popo, o  + 125, 260, 1);
        if (perso.popo->objet.potion != SOIN && perso.popo->objet.potion != SOIN){
            MLV_draw_text_with_font(o + 160, 275,"%d", stat, MLV_COLOR_WHITE, perso.popo->actif);
        }
    }
    

    MLV_draw_text_with_font(o + 10 , 300, "E : mode =", font, MLV_COLOR_WHITE);
    if (perso.modeAtk == MELEE){
        afficherItem(sprite.ekip_arme_actif, o + 160, 300);
    } else {
        afficherItem(sprite.ekip_baguette_actif, o + 160, 300);
    }
    

    MLV_free_font(font);
    MLV_free_font(stat);
}

void afficherInventaire(Inventaire invent){
    MLV_Font *font;
    MLV_Font *stat;
    int o, oy, i, j;
    
    o = TAILLE_CASE * NB_CASE_X;
    oy = 345;
    font = MLV_load_font("sprite/Pixeloid.ttf", 27);
    stat = MLV_load_font("sprite/Pixeloid.ttf", 15);

    MLV_draw_filled_rectangle(o, oy, TAILLE_X - o, TAILLE_Y - oy, MLV_COLOR_BLACK);
    
    for (i = 0; i < NB_ITEM_MAX / 4; i++){
        for (j = 0; j < 4; j++){
            MLV_draw_filled_rectangle(o + 15 + (i * (TAILLE_ITEM + 15)), oy  + (j * (TAILLE_ITEM + 15)), TAILLE_ITEM, TAILLE_ITEM, BACKGROUND);
            if (invent.content[i * 4 + j]->type != VIDE){      
                afficherItemDansInventaire(*invent.content[i * 4 + j], o + 15 + (i * (TAILLE_ITEM + 15)), oy  + (j * (TAILLE_ITEM + 15)), 0);
            }
        }
    }
    MLV_draw_text_with_font(o + 15 , TAILLE_Y - 50, "I : Inventory", font, MLV_COLOR_WHITE);
    
    MLV_free_font(font);
    MLV_free_font(stat);
}

void afficherItem(MLV_Image *sprite,int x, int y){
    MLV_draw_image(sprite, x, y);
}

void afficherHero(Position *player){
    if(player->direction == EAST || player->direction == SOUTH){
        afficherCase(sprite.hero_east, 6, 4);
    } else if (player->direction == NORTH){
        afficherCase(sprite.hero_north, 6, 4);
    } else if (player->direction == WEST) {
        afficherCase(sprite.hero_west, 6, 4);
    } else {
        fprintf(stderr, "Erreur >> position du hero inconnue : %d\n", player->direction);
        
    }
}

void afficherTresor(Tresor *tresor, int x, int y){
    switch (tresor->ouvert)
    {
    case 0:
        afficherCase(sprite.treasure, x, y);
        break;
    
    case 1:
        if (tresor->first == NULL || tresor->second == NULL){
            afficherCase(sprite.treasure_open_empty, x, y);
        } else {
            afficherCase(sprite.treasure_open, x, y);
        }
        break;

    default:
        fprintf(stderr, "Erreur >> tresor dans un état inconnu : %d\n", tresor->ouvert);
        break;
    }
}

void afficherMonstre(Monstre *monstre,  int x, int y){
    switch (monstre->direction)
    {
    case EAST:
        afficherCase(sprite.monster_east, x, y);
        break;

    case SOUTH:
        afficherCase(sprite.monster_east, x, y);
        break;

    case NORTH:
        afficherCase(sprite.monster_north, x, y);
        break;

    case WEST:
        afficherCase(sprite.monster_west, x, y);
        break;
    
    default:
        fprintf(stderr, "Erreur >> Position du monstre inconnue : %d\n", monstre->direction);
        afficheMonstre(monstre);
        break;
    }
}

int convertMLVtoDirection(MLV_Keyboard_button touche){
    switch (touche)
    {
    case 'z':
    case MLV_KEYBOARD_UP:
        return NORTH;
    
    case 'd':
    case MLV_KEYBOARD_RIGHT:
        return EAST;

    case 'q':
    case MLV_KEYBOARD_LEFT:
        return WEST;
    
    case 's':
    case MLV_KEYBOARD_DOWN:
        return SOUTH;

    default:
        break;
    }

    return touche;
}

void afficherItemDansInventaire(Item item, int x, int y, int actif){
    MLV_Font *font;
    MLV_Font *stat;

    font = MLV_load_font("sprite/Pixeloid.ttf", 30);
    stat = MLV_load_font("sprite/Pixeloid.ttf", 15);

    switch (item.type)
    {
        case EQUIPEMENT:
            switch (item.objet.equipement)
            {
                case ARMURE:
                    if (actif == 1){
                        afficherItem(sprite.ekip_armure_actif, x, y);
                    } else {
                        afficherItem(sprite.ekip_armure, x, y);
                    }
                    break;

                case ARME:
                    if (actif == 1){
                        afficherItem(sprite.ekip_arme_actif, x, y);
                    } else {
                        afficherItem(sprite.ekip_arme, x, y);
                    }   
                    break;

                case BAGUETTE:
                    if (actif == 1){
                        afficherItem(sprite.ekip_baguette_actif, x, y);    
                    } else {
                        afficherItem(sprite.ekip_baguette, x, y);
                    }
                    
                    break;
                    
                default:
                    fprintf(stderr, "Erreur >> Type d'equipement inconnu : %d\n", item.objet.equipement);
                    MLV_draw_text_with_font(x, y, "Eki", font, MLV_COLOR_WHITE);
                    break;
            }
            if (actif == 1){
                MLV_draw_text_with_font(x + 40, y + 20, "%d", stat, MLV_COLOR_WHITE, item.qualite);
            } else {
                MLV_draw_text_with_font(x + 30, y + 35, "%d", stat, MLV_COLOR_WHITE, item.qualite);
            }
            break;

        case POPO:
            switch (item.objet.potion)
            {
            case SOIN:
                if (actif == 1){
                    afficherItem(sprite.popo_soin_actif, x, y);
                } else {
                    afficherItem(sprite.popo_soin, x, y);
                }
                
                break;

            case MAGIE:
                if (actif == 1){
                    afficherItem(sprite.popo_magie_actif, x, y);
                } else {
                    afficherItem(sprite.popo_magie, x, y);
                }
                break;

            case REGEN:
                if (actif == 1){
                    afficherItem(sprite.popo_regen_actif, x, y);
                } else {
                    afficherItem(sprite.popo_regen, x, y);
                }
                break;
                    
            case PRECISION:
                if (actif == 1) {
                    afficherItem(sprite.popo_precision_actif, x, y);
                } else {
                    afficherItem(sprite.popo_precision, x, y);
                }
                break;

            case APPRENTISSAGE:
                if (actif == 1) {
                    afficherItem(sprite.popo_apprentissage_actif, x, y);
                } else {
                    afficherItem(sprite.popo_apprentissage, x, y);
                }
                break;

            default:
                fprintf(stderr, "Erreur >> Type de potion inconnue : %d\n", item.objet.potion);
                MLV_draw_text_with_font(x, y, "Pot", font, MLV_COLOR_WHITE);
                break;
            }
            break;
                
        default:
            MLV_draw_text_with_font(x, y, "???", font, MLV_COLOR_WHITE);
            break;
    }
    
    MLV_free_font(font);
    MLV_free_font(stat);   
}

void utiliserInventaire(Perso *perso, Inventaire *invent){
    MLV_Keyboard_button touche;
    MLV_Font *font;
    MLV_Font *stat;
    Mouse mouse;
    int x, y, o, oy, direction, souris;
    
    
    o = TAILLE_CASE * NB_CASE_X;
    oy = 345;
    x = y = 0;
    touche = -1;
    souris = -1;
    font = MLV_load_font("sprite/Pixeloid.ttf", 25);
    stat = MLV_load_font("sprite/Pixeloid.ttf", 15);

    while (touche != MLV_KEYBOARD_ESCAPE && sourisEstSurRetour(mouse) == 0){
        afficherInventaire(*invent);
        direction = -1;
        direction = convertMLVtoDirection(touche);
        souris = sourisEstSurItem(mouse);
        MLV_draw_filled_rectangle(o + 15, TAILLE_Y - 55, TAILLE_ITEM * 3 + 30, 75, MLV_COLOR_BLACK);
        /*un tour de jeu*/
        if (direction < 4  && direction >= 0){
            switch (direction)
            {
            case NORTH:
                y = (y - 1) % 4; 
                break;
            
            case SOUTH:
                y = (y + 1) % 4; 
                break;

            case EAST:
                x = (x + 1) % 3; 
                break;

            case WEST:
                x = (x - 1) % 3; 
                break;

            default:
                break;
            }
            if (x < 0)
                x+=3;
            if (y < 0)
                y+=4;

            MLV_draw_filled_rectangle(o + 15 + (x * (TAILLE_ITEM + 15)), oy + (y * (TAILLE_ITEM + 15)), TAILLE_ITEM, TAILLE_ITEM, MLV_COLOR_BLUE);
            
            if (invent->content[y + x * 4]->type != VIDE){
                afficherItemDansInventaire(*invent->content[y + x * 4], o + 15 + (x * (TAILLE_ITEM + 15)), oy + (y * (TAILLE_ITEM + 15)), 0);
                MLV_draw_text_with_font(o + 15 + 30, TAILLE_Y - 55, "T : Throw", font, MLV_COLOR_WHITE);
                if (invent->content[y + x * 4]->type == POPO){
                    MLV_draw_text_with_font(o + 15 + 40, TAILLE_Y - 30, "E : Drink", font, MLV_COLOR_WHITE);
                } else {
                    MLV_draw_text_with_font(o + 15 + 40, TAILLE_Y - 30, "E : Equip", font, MLV_COLOR_WHITE);
                }
            }
            
            
        } else if (souris >= 0){
            
            x = souris / 4;
            y = souris - x * 4;

            MLV_draw_filled_rectangle(o + 15 + (x * (TAILLE_ITEM + 15)), oy + (y * (TAILLE_ITEM + 15)), TAILLE_ITEM, TAILLE_ITEM, MLV_COLOR_BLUE);
            
            if (invent->content[y + x * 4]->type != VIDE){
                afficherItemDansInventaire(*invent->content[y + x * 4], o + 15 + (x * (TAILLE_ITEM + 15)), oy + (y * (TAILLE_ITEM + 15)), 0);
                MLV_draw_text_with_font(o + 15 + 30, TAILLE_Y - 55, "T : Throw", font, MLV_COLOR_WHITE);
                if (invent->content[y + x * 4]->type == POPO){
                    MLV_draw_text_with_font(o + 15 + 40, TAILLE_Y - 30, "E : Drink", font, MLV_COLOR_WHITE);
                } else {
                    MLV_draw_text_with_font(o + 15 + 40, TAILLE_Y - 30, "E : Equip", font, MLV_COLOR_WHITE);
                }
            }
            
        } else if (invent->content[y + x * 4]->type != VIDE){
            MLV_draw_filled_rectangle(o + 15 + (x * (TAILLE_ITEM + 15)), oy + (y * (TAILLE_ITEM + 15)), TAILLE_ITEM, TAILLE_ITEM, MLV_COLOR_BLUE);
            if (invent->content[y + x * 4]->type != VIDE){
                afficherItemDansInventaire(*invent->content[y + x * 4], o + 15 + (x * (TAILLE_ITEM + 15)), oy + (y * (TAILLE_ITEM + 15)), 0);
                MLV_draw_text_with_font(o + 15 + 30, TAILLE_Y - 55, "T : Throw", font, MLV_COLOR_WHITE);
                if (invent->content[y + x * 4]->type == POPO){
                    MLV_draw_text_with_font(o + 15 + 40, TAILLE_Y - 30, "E : Drink", font, MLV_COLOR_WHITE);
                } else {
                    MLV_draw_text_with_font(o + 15 + 40, TAILLE_Y - 30, "E : Equip", font, MLV_COLOR_WHITE);
                }
            }
            
            if (direction == 't' || sourisEstSurJeter(mouse)){
                jetteItem(invent, invent->content[y + x *4]);
                MLV_draw_filled_rectangle(o + 15 + (x * (TAILLE_ITEM + 15)), oy + (y * (TAILLE_ITEM + 15)), TAILLE_ITEM, TAILLE_ITEM, MLV_COLOR_BLUE);
                MLV_draw_filled_rectangle(o + 15, TAILLE_Y - 55, TAILLE_ITEM * 3 + 30, 75, MLV_COLOR_BLACK);
            }
            if (direction == 'e' || sourisEstSurEquiper(mouse)){
                equipeItem(perso, invent, invent->content[y + x *4]);
                afficherStat(*perso);
                MLV_draw_filled_rectangle(o + 15 + (x * (TAILLE_ITEM + 15)), oy + (y * (TAILLE_ITEM + 15)), TAILLE_ITEM, TAILLE_ITEM, MLV_COLOR_BLUE);
                MLV_draw_filled_rectangle(o + 15, TAILLE_Y - 55, TAILLE_ITEM * 3 + 30, 75, MLV_COLOR_BLACK);
            }
            
        } else {
            MLV_draw_filled_rectangle(o + 15 + (x * (TAILLE_ITEM + 15)), oy + (y * (TAILLE_ITEM + 15)), TAILLE_ITEM, TAILLE_ITEM, MLV_COLOR_BLUE);
            
        }
        touche = -1;
        
        MLV_actualise_window();
        MLV_wait_keyboard_or_mouse(&touche, NULL, NULL, &mouse.x, &mouse.y);
        
    };
    MLV_free_font(font);
    MLV_free_font(stat);
}

int afficherGameOver(int *nouvelle_partie){
    MLV_Font *font;
    MLV_Font *bouton;
    MLV_Font *stat;
    int mouse_x, mouse_y;
    MLV_clear_window(BACKGROUND);

    font = MLV_load_font("sprite/Pixeloid.ttf", 50);
    bouton = MLV_load_font("sprite/Pixeloid.ttf", 30);
    stat = MLV_load_font("sprite/Pixeloid.ttf", 15);
    MLV_draw_text_with_font(TAILLE_X / 2 - 150, 100, "GAME OVER", font, MLV_COLOR_WHITE);
    MLV_draw_image(sprite.game_over, TAILLE_X / 2 - 350, 150);
    MLV_draw_text_with_font(TAILLE_X / 2 - 75, 150, "level reaching : 123", stat, MLV_COLOR_WHITE);

    MLV_draw_filled_rectangle(TAILLE_X/2 - 200, TAILLE_Y - 50, 235, 45, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(TAILLE_X/2 - 195, TAILLE_Y - 45, 225, 35, BACKGROUND);
    MLV_draw_text_with_font(TAILLE_X/2 - 190, TAILLE_Y - 45, "Back to Menu",bouton, MLV_COLOR_WHITE);

    MLV_draw_filled_rectangle(TAILLE_X/2 + 75, TAILLE_Y - 50, 125, 45, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(TAILLE_X/2 + 80, TAILLE_Y - 45, 115, 35, BACKGROUND);
    MLV_draw_text_with_font(TAILLE_X/2 + 85, TAILLE_Y - 45, "Leave", bouton, MLV_COLOR_WHITE);

    MLV_actualise_window();
    while (1){
        MLV_wait_mouse(&mouse_x, &mouse_y);
        if (mouse_y >= TAILLE_Y - 50 && mouse_y <= TAILLE_Y - 5){
            
            if (mouse_x >= TAILLE_X/2 - 200 && mouse_x <= TAILLE_X/2 + 35){
                *nouvelle_partie = 1;
                MLV_free_font(font);
                MLV_free_font(bouton);
                MLV_free_font(stat);
                return 1;
            }

            if (mouse_x >= TAILLE_X/2 + 75 && mouse_x <= TAILLE_X/2 + 200){
                *nouvelle_partie = 0;
                MLV_free_font(font);
                MLV_free_font(bouton);
                MLV_free_font(stat);
                return 0;
            }
        }
    }

    MLV_free_font(font);
    MLV_free_font(bouton);
    MLV_free_font(stat);
    return 1;
}

int naviguerMenu(int *nouvelle_partie) {
    int mouse_x, mouse_y;
    MLV_clear_window(BACKGROUND);

    afficherMenu(nouvelle_partie);

    MLV_actualise_window();
    
    while (1){
        MLV_wait_mouse(&mouse_x, &mouse_y);
        if (mouse_x >= TAILLE_X - 300 && mouse_x <= TAILLE_X - 75){
            
            if (mouse_y >=175 && mouse_y <= 220){
                *nouvelle_partie = 1;
                return 1;
            }
            if (mouse_y >=275 && mouse_y <= 320 && *nouvelle_partie == 2){
                return 2;
            }
            if (mouse_y >=375 && mouse_y <= 420){
                *nouvelle_partie = 3;
                printf("Chargement du plateau\n");
                return 3;
            }
            if (mouse_y >=475 && mouse_y <= 520){
                afficherCreditTuto();
                MLV_actualise_window();
                MLV_wait_mouse(&mouse_x, &mouse_y);
                afficherMenu(nouvelle_partie);
                MLV_actualise_window();
                mouse_x = 0;
                mouse_y = 0;
            }
            if (mouse_y >=575 && mouse_y <= 620){
                *nouvelle_partie = 0;
                return 0;
            }
        }
    }
    return 0;
}

void afficherCreditTuto(){
    MLV_Font *bouton, *font;

    font = MLV_load_font("sprite/Pixeloid.ttf", 50);
    bouton = MLV_load_font("sprite/Pixeloid.ttf", 30);

    MLV_clear_window(BACKGROUND);
    MLV_draw_text_with_font(100, 25, "Essaie d'aller le plus loin possible !", font, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(75, 100, ". Utilise les fleches ou Z,Q,S,D pour te deplacer", bouton, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(75, 150, ". Deplace toi devant un monstre le taper", bouton, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(75, 200, ". Tu peux changer de mode d'attaque en appuyant sur E", bouton, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(75, 250, ". Deplace toi devant un coffre pour le fouiller", bouton, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(75, 300, ". Appuie sur l'inventaire ou sur I pour y acceder", bouton, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(75, 350, ". tu peux équiper ou jeter ton item selectionné avec E et T", bouton, MLV_COLOR_WHITE);

    afficherItem(sprite.popo_soin, 75, 400);
    MLV_draw_text_with_font(125, 410, "restaure 10%% des hp", bouton, MLV_COLOR_WHITE);
    
    afficherItem(sprite.popo_magie, 600, 400);
    MLV_draw_text_with_font(650, 410, "restaure 10%% des mp", bouton, MLV_COLOR_WHITE);
    
    afficherItem(sprite.popo_regen, 75, 460);
    MLV_draw_text_with_font(125, 460, "restaure 20 hp et 10 mp", bouton, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(125, 485, "pendant 30 tours", bouton, MLV_COLOR_WHITE);
    
    afficherItem(sprite.popo_precision, 600, 460);
    MLV_draw_text_with_font(650, 460, "augmente la chance de coup", bouton, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(650, 485, "critique pendant 30 tours", bouton, MLV_COLOR_WHITE);
    
    afficherItem(sprite.popo_apprentissage, 75, 520);
    MLV_draw_text_with_font(125, 530, "augmente les points d'xp gagnés de 30%% pendant 30 tours", bouton, MLV_COLOR_WHITE);

    MLV_draw_text_with_font(25, TAILLE_Y - 50, "Projet réalisé par Césaire Agonsè (2021-2022)", bouton, MLV_COLOR_WHITE);

    free(bouton);
    free(font);
}

void afficherMenu(int *nouvelle_partie){
    MLV_Font *font;
    MLV_Font *bouton;
    MLV_clear_window(BACKGROUND);

    font = MLV_load_font("sprite/Pixeloid.ttf", 50);
    bouton = MLV_load_font("sprite/Pixeloid.ttf", 30);
    MLV_draw_text_with_font(TAILLE_X / 2 - 275, 75, "DONJON ROGUE LIKE", font, MLV_COLOR_WHITE);
    MLV_draw_image(sprite.menu, TAILLE_X / 2 - 550, 200);

    MLV_draw_filled_rectangle(TAILLE_X - 300, 175, 225, 45, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(TAILLE_X - 295, 180, 215, 35, BACKGROUND);
    MLV_draw_text_with_font(TAILLE_X - 290, 180, "New Game", bouton, MLV_COLOR_WHITE);

    
    if (*nouvelle_partie == 1){
        MLV_draw_filled_rectangle(TAILLE_X - 300, 275, 225, 45, MLV_COLOR_BLACK);
        MLV_draw_filled_rectangle(TAILLE_X - 295, 280, 215, 35, BACKGROUND);
        MLV_draw_text_with_font(TAILLE_X - 290, 280, "Resume", bouton, MLV_COLOR_BLACK);
    }else{
        MLV_draw_filled_rectangle(TAILLE_X - 300, 275, 225, 45, MLV_COLOR_WHITE);
        MLV_draw_filled_rectangle(TAILLE_X - 295, 280, 215, 35, BACKGROUND);
        MLV_draw_text_with_font(TAILLE_X - 290, 280, "Resume", bouton, MLV_COLOR_WHITE);
    }
    

    MLV_draw_filled_rectangle(TAILLE_X - 300, 375, 225, 45, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(TAILLE_X - 295, 380, 215, 35, BACKGROUND);
    MLV_draw_text_with_font(TAILLE_X - 290, 380, "Load Save", bouton, MLV_COLOR_WHITE);

    MLV_draw_filled_rectangle(TAILLE_X - 300, 475, 225, 45, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(TAILLE_X - 295, 480, 215, 35, BACKGROUND);
    MLV_draw_text_with_font(TAILLE_X - 290, 480, "Credits&Tuto", bouton, MLV_COLOR_WHITE);

    MLV_draw_filled_rectangle(TAILLE_X - 300, 575, 225, 45, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(TAILLE_X - 295, 580, 215, 35, BACKGROUND);
    MLV_draw_text_with_font(TAILLE_X - 290, 580, "Leave", bouton, MLV_COLOR_WHITE);

    MLV_free_font(font);
    MLV_free_font(bouton);
}

int sourisEstSurRetour(Mouse mouse){
    
    if (mouse.x >= TAILLE_CASE * NB_CASE_X - 110 && mouse.x <= TAILLE_CASE * NB_CASE_X - 10 && mouse.y >= TAILLE_Y - 50 && mouse.y <= TAILLE_Y - 5)
        return 1;

    return 0;
}

int sourisEstSurInventaire(Mouse mouse){
    
    if (mouse.x >= TAILLE_CASE * NB_CASE_X && mouse.y >= 345)
        return 1;

    return 0;
}

int sourisEstSurAttaque(Mouse mouse){
    
    if (mouse.x >= TAILLE_CASE * NB_CASE_X && mouse.y >= 300 && mouse.y <= 340)
        return 1;

    return 0;
}

int sourisEstSurItem(Mouse mouse){

    int i, j, x, y;
    int ox, oy;
    ox = TAILLE_CASE * NB_CASE_X;
    oy = 345;
    
    x = -1;
    y = -1;

    for (i = 0; i < NB_ITEM_MAX / 4; i++){
        if (mouse.x >= ox + 15 + (i * (TAILLE_ITEM + 15)) && mouse.x <= ox + 15 + (i * (TAILLE_ITEM + 15)) + TAILLE_ITEM){
            x = i;
        }
    }
    for (j = 0; j < 4; j++){
        if (mouse.y >= oy + (j * (TAILLE_ITEM + 15)) && mouse.y <= oy + (j * (TAILLE_ITEM + 15)) + TAILLE_ITEM){
            y = j;
        }
    }
    
    if (x < 0 || y < 0){
        return -1;
    }

    return x * 4 + y;
}

int sourisEstSurJeter(Mouse mouse){
    int o;
    o = TAILLE_CASE * NB_CASE_X;
    if (mouse.x >= o + 15 + 30 && mouse.x <= TAILLE_X - 15 - 30 && mouse.y >= TAILLE_Y - 60 &&  mouse.y <= TAILLE_Y - 30)
        return 1;

    return 0;
}

int sourisEstSurEquiper(Mouse mouse){
    int o;
    o = TAILLE_CASE * NB_CASE_X;
    if (mouse.x >= o + 15 + 30 && mouse.x <= TAILLE_X - 15 - 30 && mouse.y >= TAILLE_Y - 60)
        return 1;

    return 0;
}