#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "piece.h"


struct piece_s{
    int x; //coordonnée x de la position de la piece (coin inf gauche)
    int y; //coordonnée y de la position de la piece (coin inf gauche)
    int width; //largeur de la piece
    int height; //hauteur de la piece
    bool move_x; //indique si la piece bouge horizontalement
    bool move_y; //indique si la piece bouge verticalement
};

piece new_piece (int x, int y, int width, int height, bool move_x, bool move_y) {
    piece p = malloc(sizeof(struct piece_s));
    p->x = x;
    p->y = y;
    p->width = width;
    p->height = height;
    p->move_x = move_x;
    p->move_y = move_y;
    return p;
}

piece new_piece_rh(int x, int y, bool small, bool horizontal){
    piece p = malloc(sizeof(struct piece_s));
    p->x = x;
    p->y = y;
    if(horizontal==true){
      p->move_x = true;
      p->move_y = false;
      if(small==true){
	p->width = 2;
	p->height = 1;
      }
      else{
	p->width = 3;
	p->height = 1;
      }
    }
    
    else{
      p->move_x = false;
      p->move_y = true;
      if(small==true){
	p->width = 1;
	p->height = 2;
      }
      else{
	p->width = 1;
	p->height = 3;
      }
    }
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
        dst->width = src->width;
        dst->height = src->height;
        dst->move_x = src->move_x;
        dst->move_y = src->move_y;
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
    return p->height;
    
}

/**
 * @brief Returns the different of abscissas of the leftmost and the rightmost points of the piece p.
 */
int get_width(cpiece p){
    return p->width;
}

bool is_horizontal(cpiece p){
    if(p->width > p->height)
        return true;
    return false;
    }  

bool can_move_x(cpiece p) { 
  return move_x;
}

bool can_move_y(cpiece p)
    return move_y;
}


bool intersect(cpiece p1, cpiece p2){
    
    int taille_p1 = get_width(p1) * get_height(p1);
    int taille_p2 = get_width(p2) * get_height(p2);
    
    int coord_p1[3][3];
    int coord_p2[3][3];
    
    if (p1->width > p1->height){
      for(int i=0; i<taille_p1; i++){
	coord_p1[i][0] = p1->x + i;
	coord_p1[i][1] = p1->y;
      }
    }
    else if (p1->width < p1->height){
      for(int i=0; i<taille_p1; i++){
	coord_p1[i][0] = p1->x;
	coord_p1[i][1] = p1->y + i;
      }
    }
     else if (p1->width == p1->height) {
       for(int i = 0; i < taille_p1; i++) {
	 coord_p1[i][0] = p1->x + i;
	 coord_p1[i][1] = p2->y + i;
      } 
    
    if (p2->width > p2->height) {
      for(int i=0; i<taille_p2; i++){
	coord_p2[i][0] = p2->x + i;
	coord_p2[i][1] = p2->y;
      }
    }
    else if(p2->width < p2->height){
       for(int i=0; i<taille_p2; i++){
           coord_p2[i][0] = p2->x;
           coord_p2[i][1] = p2->y + i;
       }
    }
    
    else if (p2->width == p2->height) {
      for(int i=0; i < taille_p2; i++) {
	coord_p2[i][0] = p2->x + i;
	coord_p2[i][1] = p2->y + i; 
      }
    } 
	
    for(int i=0; i<taille_p1; i++){
      for(int j=0; j<taille_p2; j++){
	if(coord_p1[i][0] == coord_p2[j][0] && coord_p1[i][1] == coord_p2[j][1])
	  return true;
      }
    }
    
    return false;
} 




