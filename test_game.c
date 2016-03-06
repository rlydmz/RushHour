#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "piece.h"

#define NB_PIECES 4



bool test_equality_int(int expected, int value, char *msg) {
    if (expected != value)
        fprintf(stderr, "ERR : value expected %d ; value computed %d. %s\n", expected, value, msg);
    return expected = value;
}

bool test_equality_bool(bool expected, bool value, char *msg) {
    if (expected != value)
        fprintf(stderr, "ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
    return expected == value;
}

/* bool test_new_game() {  // Faire ces 4 fonctions si necessaires
    return 0;
}

bool test_copy() {
    
}

bool test_game_nb_piece() {
    return 0;
}

bool test_piece_move() {
    return 0;
}

*/


int main(int argc, const char * argv[]) {
    
    piece pieces[NB_PIECES];
    pieces[0] = new_piece_rh(3, 3, true, true);    // Pas sur de la necessité içi
    pieces[1] = new_piece_rh(3, 0, true, false);   // idem
    pieces[2] = new_piece_rh(4, 1, true, true);    // idem
    pieces[3] = new_piece_rh(5, 3, false, false);  // idem
    
    game g = new_game_hr(NB_PIECES, pieces);
    printf("La partie g a été faite.\n");
    
    game c = new_game_hr(0, pieces);
    copy_game(g,c);
    printf("La partie g a bien été copiée dans c");
    
    //game_nb_pieces(g);              Pas sur de ça
    //printf("Il y a %d pieces", g);  Pas sur de ça
    
    play_move(c, 1, LEFT, 2);
    printf("La piece %d de la partie c a bouger à %c d'une distance %d\n", piece[1], d, distance); //A modifié
    if (game_over_hr(c)) {
        printf("You win !\n");
        printf("Niveau suivant ?!\n");
    }
    // Completer la suite
    
    
    delete_game(c);
    printf("La partie c a bien été supprimé");
        
    
    

}
