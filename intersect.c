
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "piece.h"
#include "game.h"

bool intersect(cpiece p1, cpiece p2){

    for(int i=get_x(p1) ; i<get_x(p1)+get_width(p1) ; i++) {        // pour tout i: abscisse de p1
        for(int j=get_y(p1) ; j<get_y(p1)+get_height(p1) ; j++) {       // pour tout j: ordonnee de p1
            for(int k=get_x(p2) ; k<get_x(p2)-get_width(p2) ; k++){         // pour tout k: abscisse de p2
                for(int l=get_y(p2) ; l<get_y(p2)+get_height(p2) ; l++){        // pour tout l: ordonnee de p2

                    if(i==k && j==l) return true;                                   // vrai si on trouve une case en commun

                }
            }
        }
    }
    return false;   // faux sinon
}
