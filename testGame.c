
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "piece.h"

#define NB_PIECES 4



bool test_equality_int(int expected, int value, char *msg) {
    if (expected != value)
        fprintf(stderr, "ERR : value expected %d ; value computed %d. %s\n", expected, value, msg);
    return expected == value;
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
    pieces[0] = new_piece_rh(0, 2, true, true);
    pieces[1] = new_piece_rh(3, 1, true, false);
    pieces[2] = new_piece_rh(5, 3, true, false);
    pieces[3] = new_piece_rh(1, 4, false, true);

    game g1 = new_game_hr(NB_PIECES, pieces);
    printf("Partie A initialisee !\n");

    game g2 = new_game_hr(0, pieces);
    printf("Partie B initialisee !\n\n");

    // copy_game(g1,g2); // ici le programme plante, ca deconne au niveau de copy_piece appellee dans copy_game
    // printf("La partie g a bien été copiée dans c");

    printf("La partie g1 compte %d pieces.\n\n", game_nb_pieces(g1));

    // ici on determine les parametres du deplacement
    dir d = RIGHT;
    int numpiece = 0;
    int distance = 1;

    //play_move(c, numpiece, d, distance);      // play_move est pas encore terminee dans game.c

    //printf("La piece %d de la partie g2 s'est deplacee de %d case(s).\n", numpiece, distance);

    piece pieces2[2];
    pieces2[0] = new_piece_rh(4, 0, true, true);  // ici la voiture rouge touche le bord droit <=> game over
    pieces2[1] = new_piece_rh(3, 2, true, false);
    game gameover = new_game_hr(2, pieces2);

    if (game_over_hr(gameover)) {  // pourtant le programme plante
        printf("You win !\n");
        printf("Niveau suivant ?\n\n");
    }

    // Completer la suite


    delete_game(g2);

    printf("suppression de la partie reussie\n\n");




}
