/* Auteur : Césaire Agonsè
 * Création: 10-01-22
 * Modification: 10-01-22 */

#ifndef __FICHIER__
#define __FICHIER__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/terrain.h"
#include "../include/position.h"
#include "../include/perso.h"
#include "../include/item.h"
#include "../include/inventaire.h"

/*entier signé de longueur 64 bits*/
typedef unsigned long long int64;

int saveEtage(Plateau **plateau, int nbEtage);

int chargerEtage(Plateau **plateau, int nbEtage);

int savePerso(Perso *perso);

int chargerPerso(Perso *perso);

int savePosition(Position *position);

int chargerPosition(Position *position);

int saveInventaire(Inventaire *inventaire);

int chargerInventaire(Inventaire *inventaire);

/*Fonction qui sert a mettre un bit à un dans un nombre*/
int64 initialiser_bit_1(int decalage);

/*Fonction qui sert a mettre un bit à 1 à un certain endroit*/
int64 mettre_bit_1(int64 x, int decalage);

/*Fonction qui sert a mettre un bit à 0 à un certain endroit*/
int64 mettre_bit_1(int64 x, int decalage);

int tester_bit_1(int64 x, int decalage);

int64 convertMonstreEnInt64(Cell case_);

int64 convertTresorEnInt64(Cell case_);

/*convertit un int64 en int dans l'intervalle de bit [firstBit,lastBit]*/
int convertInt64EnInt(int64 n, int firstBit, int lastBit);

/*convertit une ligne d'étage en int64 pour tout les cases de type type*/
int64 *convertPlateauEnLigne(Plateau *plateau, Celltype type);

/*convertit en int64 les attribut d'un perso. Dans le projet les attributs en guise de parametre seront:
* (hp,mp,atk,inte), (def,exp,lv,crit), (bonus_exp, mode_atk, 0, 0)*/
int64 convertPersoEnInt64(int hp_def_bonus_exp, int mp_exp_mode_atk, int atk_lv, int inte_crit);

int64 convertItemEnInt64(Item *item);

Item *convertInt64EnItem(int64 n);
#endif