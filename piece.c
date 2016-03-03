#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "piece.h"

struct piece_s{
  int x; //coordonnée x de la position du véhicule(coin sup gauche)
  int y; //coordonnée y de la position du véhicule(coin sup gauche)
  bool small; //si true voiture, si faux camion
  bool horizontal; //si true bouge horizontalement, si faux verticalement
};



piece new_piece_rh(int x, int y, bool small, bool h){
  piece p = malloc(sizeof(struct piece_s));
  p->x = x;
  p->y = y;
  p->small = small;
  p->horizontal = h;
  return p;
}


void delete_piece (piece p){
  if(p!=NULL)
    free(p);
}

void copy_piece (cpiece src, piece dst){
  if(src != NULL && dst != NULL){
    dst->x = src->x;
    dst->y = src->y;
    dst->small = src->small;
    dst->horizontal = src->horizontal;
  }
}

void move_piece(piece p, dir d, int distance){
    if(p!=NULL && distance !=0 ){
            if(!is_horizontal(p)){
                if(d == DOWN){
                    p->y -= distance;
                }
                else if(d == UP){
                    p->y += distance;
                }
            }
            else{
                if(d == LEFT){
                    p->x -= distance;
                }
                else if(d == RIGHT){
                    p->x += distance;
                }
            }
    }
}


/**
 * @brief Returns the abscissa of leftmost point of the piece p.
 */
int get_x(cpiece p){
        return p->x;
}

/**
 * @brief Returns the ordinate of lowest point of the piece p.
 */
int get_y(cpiece p){
        return p->y;
}

/**
 * @brief Returns the different of ordinates of the uppermost and the lowest points of the piece p.
 */
int get_height(cpiece p){
    if(p!=NULL){
        if(is_horizontal(p))
            return 1;
        else{
            if(p->small)
                return 2;
            else
                return 3;

        }
    }
    else
        return -1;

}

/**
 * @brief Returns the different of abscissas of the leftmost and the rightmost points of the piece p.
 */
int get_width(cpiece p){

    if(p!=NULL){
        if(!is_horizontal(p))
            return 1;
        else{
            if(p->small)
                return 2;
            else
                return 3;
        }
    }
    else
        return -1;
}

bool is_horizontal(cpiece p){
    if(p->horizontal)
        return true;
    return false;
}

bool intersect(cpiece p1, cpiece p2){

  int taillep1 = get_width(p1) * get_height(p1);
  int taillep2 = get_width(p2) * get_height(p2);

  int coordp1[3][2];
  int coordp2[3][2];

  if(is_horizontal(p1)){
    for(int i=0; i<taillep1; i++){
      coordp1[i][0] = p1->x + i;
      coordp1[i][1] = p1->y;
    }
  }
  else{
    for(int i=0; i<taillep1; i++){
      coordp1[i][0] = p1->x;
      coordp1[i][1] = p1->y + i;
    }
  }

  if(is_horizontal(p2)){
    for(int i=0; i<taillep2; i++){
      coordp2[i][0] = p2->x + i;
      coordp2[i][1] = p2->y;
    }
  }
  else{
    for(int i=0; i<taillep2; i++){
      coordp2[i][0] = p2->x;
      coordp2[i][1] = p2->y + i;
    }
  }

  for(int i=0; i<taillep1; i++){
    for(int j=0; j<taillep2; j++){
      if(coordp1[i][0] == coordp2[j][0] && coordp1[i][1] == coordp2[j][1])
	 return true;
    }
  }

    return false;

};
