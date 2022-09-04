/* Auteur : Césaire Agonsè
 * Création: 21-11-21
 * Modification: 22-11-21 */

#ifndef __ACTION__
#define __ACTION__

#include <stdio.h>
#include <stdlib.h>

#include "../include/terrain.h"
#include "../include/perso.h"
#include "../include/monstre.h"
#include "../include/inventaire.h"
#include "../include/position.h"

/*Regarde si tout les monstre du plateau ont 0 hp ou moins
* si oui puis le libère dans le paradis de la mémoire et
* laisse apparaitre un trésor sur sa case
* le type de la case devient donc TREASURE
* sinon ne fait rien*/
void supprimerMonstres(Plateau *etage, Perso *perso);

/*La meme chose que supprimer_monstres mais avec les tresors
* le type de la case devient donc ROOM*/
void supprimerTresors(Plateau *etage);

/*EST INUTILE*/
/*Deplace le perso (bah oe lojik)
* Position est la position du perso
* Retourne 1 si le perso arrive à se deplacer retourne 0 sinon*/
int deplacePerso(Position *position, Plateau *etage, Direction direction);

/*Le Perso subit l'attaque de monstre*/
void subitAttaque(Perso *perso, Monstre *monstre);

/*Le Perso attaque (selon son mode) le monstre et celui ci subit des dégats*/
void lanceAttaque(Perso *perso, Monstre *monstre);

/*fouille un tresor lance ajoute_item si necessaire
* ajoute 1 ou 2 items selon la situation
* si le tresor n'est pas vide ou que l'inventaire n'est pas
* plein alors la fonction retourne 1, 0 sinon*/
int fouilleTresor(Inventaire *invent, Tresor *tresor);

/*Le perso subit les attaques des monstres si il y en a sur les cases adjacentes*/
void monstreAttaque(Perso *perso, Position position, Plateau *etage);

/*equipe l'item present dans l'inventaire grâce à remplaceItemActif 
* et vide sa place dans l'inventaire*/
void equipeItem(Perso *perso, Inventaire *invent, Item *item);

/*ajoute l'item (qui sera actif en jeu) à l'emplacement dédié dans perso*/
void remplaceItemActif(Perso *perso, Item *item);

/*actualise l'effet des potions actives et libère l'item dans le neant
* si tout ses tours d'activités sont passés*/
void actualiseEffetPotion(Perso *perso);

/*actualise l'effet des potions actives et libère l'item dans le neant
* si tout ses tours d'activités sont passés*/
void actualiseEquipement(Perso *perso, Inventaire *invent);

/*Fontion qui lance toutes les fonctions necessaire pour gerer un tour
* Renvoie 1 si un tour est bien effectué, 0 si à la fin de ce tour le perso meurt
* Renvoie -1 si il y a une erreur*/
int effectuerTour(Plateau **plateau, Perso *perso, Position *position, Inventaire *invent, int direction);

/* Fonction regarde si le joueur est sur un escalier grâce à
* la position et change l'etage en cours si c'est le cas 
* Renvoie 1 si il monte, -1 si il descend, 0 sinon, -2 si erreur*/
int changeEtage(Plateau **plateau, Position *position);

#endif