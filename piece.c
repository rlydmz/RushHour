#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "piece.h"


struct piece_s {
     int x; //coordonnée x de la position de la piece (coin inf gauche)
     int y; //coordonnée y de la position de la piece (coin inf gauche)
     int width; //largeur de la piece
     int height; //hauteur de la piece
     bool move_x; //indique si la piece bouge horizontalement
     bool move_y; //indique si la piece bouge verticalement
 };

piece new_piece (int x, int y, int width, int height, bool move_x, bool move_y) {
    piece p = (piece)malloc(sizeof(struct piece_s));
     p->x = x;
     p->y = y;
     p->width = width;
     p->height = height;
     p->move_x = move_x;
     p->move_y = move_y;
     return p;
 }

piece new_piece_rh(int x, int y, bool small, bool horizontal) {
    piece p = (piece)malloc(sizeof(struct piece_s));
    p->x = x;
    p->y = y;
    if(horizontal==true) {
        p->move_x = true;
        p->move_y = false;
        if(small==true) {
            p->width = 2;
            p->height = 1;
        }
        else {
            p->width = 3;
            p->height = 1;
        }
    }

    else {
        p->move_x = false;
        p->move_y = true;
        if(small==true) {
            p->width = 1;
            p->height = 2;
        }
        else {
            p->width = 1;
            p->height = 3;
        }
     }
     return p;
 }



void delete_piece (piece p) {
     if(p!=NULL)
         free(p);
 }

void copy_piece (cpiece src, piece dst) {
    if(src != NULL && dst != NULL) {
         dst->x = src->x;
         dst->y = src->y;
         dst->width = src->width;
         dst->height = src->height;
         dst->move_x = src->move_x;
         dst->move_y = src->move_y;
     }
 }


 /**
  * @brief Returns the abscissa of leftmost point of the piece p.
  */
int get_x(cpiece p) {
     return p->x;
 }

 /**
  * @brief Returns the ordinate of lowest point of the piece p.
  */
int get_y(cpiece p) {
     return p->y;
 }

 /**
  * @brief Returns the different of ordinates of the uppermost and the lowest points of the piece p.
  */
int get_height(cpiece p) {
     return p->height;
 }

 /**
  * @brief Returns the different of abscissas of the leftmost and the rightmost points of the piece p.
  */
int get_width(cpiece p) {
     return p->width;
 }

bool is_horizontal(cpiece p) {
     if(p->width > p->height)
         return true;
     return false;
}

bool can_move_x(cpiece p) {
    return p->move_x;
 }

bool can_move_y(cpiece p) {
     return p->move_y;
 }


bool intersect(cpiece p1, cpiece p2) {

     for(int i=get_x(p1) ; i<get_x(p1)+get_width(p1) ; i++) {        // pour tout i: abscisse de p1
         for(int j=get_y(p1) ; j<get_y(p1)+get_height(p1) ; j++) {       // pour tout j: ordonnee de p1
            for(int k=get_x(p2) ; k<get_x(p2)+get_width(p2) ; k++) {        // pour tout k: abscisse de p2
                for(int l=get_y(p2) ; l<get_y(p2)+get_height(p2) ; l++) {       // pour tout l: ordonnee de p2

                     if(i==k && j==l) return true;                                   // vrai si on trouve une case en commun

                 }
             }
         }
     }
     return false;   // faux sinon

 }

void move_piece(piece p, dir d, int distance) {
    if (p!=NULL && distance !=0) {
        if(can_move_x(p) && can_move_y(p)) {
            if(d==DOWN) {
                p->y -= distance;
            }
            if(d==UP) {
                p->y += distance;
            }
            if(d==LEFT) {
                p->x -= distance;
            }
            if(d==RIGHT) {
                p->x += distance;
            }
        }
        else if(can_move_y(p)) {
            if(d==DOWN) {
                p->y -= distance;
            }
            else if(d==UP) {
                p->y += distance;
            }
        }
        else if(can_move_x(p)) {
            if(d==LEFT) {
                p->x -= distance;
            }
            else if(d==RIGHT) {
                p->x += distance;
            }
        }
     }
 }
