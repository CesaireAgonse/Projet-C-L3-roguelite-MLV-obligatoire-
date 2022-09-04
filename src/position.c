/* Auteur : Césaire Agonsè
 * Création: 21-10-21
 * Modification: 05-01-22 */

#include "../include/position.h"

Position* initialisePosition(int x, int y){
    Position *position;
    position = (Position *) malloc(sizeof(Position));

    if (position == NULL){
        return NULL;
    }

    position->x = x;
    position->y = y;
    position->direction = EAST;
    position->etage = 0;
    position->nbEtageMax = 0;
    
    return position;
}

int deplacerJoueur(Plateau plateau, Position *player, Direction direction){
    switch (direction)
    {
    case NORTH:
        player->direction = direction;
        player->y -= 1;
        break;
    
    case EAST:
        player->direction = direction;
        player->x += 1;
        break;

    case SOUTH:
        player->direction = direction;
        player->y += 1;
        break;

    case WEST:
        player->direction = direction;
        player->x -= 1;
        break;
    
    default:
        fprintf(stderr, "Erreur >> Direction inconnue dans deplaceJoueur : %d", direction);
        return 0;
        break;
    }
    /*regarder si la case d'a coté est une case de salle*/
    return 1;
}