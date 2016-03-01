#include "piece.h"
#include <stdlib.h>
#include <stdio.h>

struct piece_s{

    //x représente l'abscisse du coup supérieur gauche de la piece
    int x;
    //y représente lordonnee du coup superieur gauche de la piece
    int y;
    //si estPetite == true, la piece sera petite, sinon et sera grande
    bool estPetite;
    //si bougeHorizontalement == true, la piece ne pourra bouger que dans l'horizontalité
    //sinon elle ne pourra bouger que dans la verticalité
    bool bougeHorizontalement;

};

piece new_piece_rh (int x, int y, bool small, bool horizontal){

    piece p = malloc(sizeof(struct piece_s));
    (*p).x = x;
    (*p).y = y;
    (*p).estPetite = small;
    (*p).bougeHorizontalement = horizontal;
    return p;

}

void delete_piece (piece p){

        free(p);

}

void copy_piece (cpiece src, piece dst){

    if(src!=NULL && dst!=NULL){
        (*dst).x = (*src).x;
        (*dst).y = (*src).y;
        (*dst).estPetite = (*src).estPetite;
        (*dst).bougeHorizontalement = (*src).bougeHorizontalement;
    }

void move_piece (piece p, dir d, int distance){

    if(p!=NULL && distance>0 && d!=NULL){
        if((*p).bougeHorizontalement == true){
            if(d==LEFT){
               (*p).y -= distance;
            }
            if(d==RIGHT){
               (*p).y += distance;
            }
        }
        else if((*p).bougeHorizontalement == false){
            if(d==UP){
                (*p).x += distance;
            }
            if(d==DOWN){
                (*p).x -= distance;
            }
        }
    }
}

bool intersect(cpiece p1, cpiece p2){



}

int get_x(cpiece p){

    if(p!=NULL)
        return (*p).x;

}

int get_y(cpiece p){

    if(p!=NULL)
        return (*p).y;

}

int get_height(cpiece p){

    if(p!=NULL){
        if((*p).bougeHorizontalement ==  true)
            return 1;
        else{
            if((*p).estPetite ==  true)
                return 2;
            else
                return 3;
        }

    }
}

}
