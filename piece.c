#include "piece.h"
#include <stdlib.h>
#include <stdio.h>

struct piece_s{

    //x représente l'abscisse du coté inférieur gauche de la piece
    int x;
    //y représente lordonnee du coté inférieur gauche de la piece
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
/*
    if(p1!=NULL && p2!=NULL){

        int nbCoteEnCommun = 0;
        int hauteurp1 = get_height(p1);
        int hauteurp2 = get_height(p2);
        int largeurp1 = get_width(p1);
        int largeurp2 = get_width(p2);

        int cptMax1, cptMax2;

        if(hauteurp1==2 || largeurp1==2)
            cptMax1 = 6;
        else if(hauteurp1==3 || largeurp1==3)
            cptMax1 = 8;

        if(hauteurp2==2 || largeurp2==2)
            cptMax2 = 6;
        else if(hauteurp2==3 || largeurp2==3)
            cptMax2 = 8;

        for(int i=0; i<cptMax1; i++){
            for(int j=0; j<cptMax2; j++){


               if(get_x(p1) == get_x(p2) && get_y(p1) == get_y(p2))
                    nbCoteEnCommun++;

            }
        }


    }
*/
}


int get_x(cpiece p){

    if(p!=NULL)
        return (*p).x;

    return 0;

}

int get_y(cpiece p){

    if(p!=NULL)
        return (*p).y;

    return 0;
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

    return 0;
}

int get_width(cpiece p){

    if(p!=NULL){
        if((*p).bougeHorizontalement ==  true){
            if((*p).estPetite ==  true)
                return 2;
            else
                return 3;
        }

        else{
                return 1;
        }

    }

    return 0;
}

}
