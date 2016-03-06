
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

bool test_new_game(piece pieces) {

    game g = new_game_hr(NB_PIECES,pieces);

    if(g==NULL){
        fprintf(stderr,"erreur le jeu n'a pas ete initialise");
        return EXIT_FAILURE;
    }

    printf("Le jeu a ete initialise..\n");
    return EXIT_SUCCESS;
}


bool test_copy(piece pieces, piece pieces2) { // ici des erreurs


    game g1 = new_game_hr(NB_PIECES,pieces);
    game g2 = new_game_hr(NB_PIECES,pieces2);

    printf("abscisse de la voiture rouge avant copy_game(): %d\n",get_x(pieces2[0]));

    copy_game(g1,g2);

    printf("abscisse de la voiture rouge apres copy_game(): %d\n",get_x(pieces2[0]));

    return 0;

}


bool test_game_nb_piece(piece pieces) {

    game g = new_game_hr(NB_PIECES,pieces);

    int nb_pieces = game_nb_pieces(g);
    printf("le jeu g possede %d pieces\n",nb_pieces);

    return 0;
}


bool test_piece_move() {

    // FONCTION TEST_PIECE_MOVE PAS ENCORE TERMINEE

    return 0;

}

bool test_game_over(piece pieces){

    game g = new_game_hr(NB_PIECES, pieces);

    bool game_over = game_over_hr(g);
    printf("jeu termine: %d\n", game_over);

    return 0;
}

bool test_delete_game(game g){

    delete_game(g);
    if(g==NULL)
        printf("La memoire occupee par le jeu a ete desallouee correctement.\n");

    return 0;
}





int main(int argc, const char * argv[]) {

    piece pieces[NB_PIECES];                        // disposition random pour test
    pieces[0] = new_piece_rh(0, 2, true, true);
    pieces[1] = new_piece_rh(3, 1, true, false);
    pieces[2] = new_piece_rh(5, 3, true, false);
    pieces[3] = new_piece_rh(1, 4, false, true);

    piece pieces_bis[NB_PIECES];                    // autre disposition random
    pieces_bis[0] = new_piece_rh(1, 1, true, true);
    pieces_bis[1] = new_piece_rh(2, 2, true, true);
    pieces_bis[2] = new_piece_rh(3, 3, true, true);
    pieces_bis[3] = new_piece_rh(4, 4, true, true);

    piece pieces_gameover[NB_PIECES];                        // disposition de fin de jeu (game over)
    pieces_gameover[0] = new_piece_rh(4, 2, true, true);     // pieces[0] en position (4,2) => voiture rouge touche le bord droit
    pieces_gameover[1] = new_piece_rh(3, 1, true, false);
    pieces_gameover[2] = new_piece_rh(5, 3, true, false);
    pieces_gameover[3] = new_piece_rh(1, 4, false, true);

    test_new_game(pieces);

    //test_copy(pieces, piece_bis); // erreurs a resoudre ici

    test_game_nb_piece(pieces);

    test_game_over(pieces_gameover);

    game g = new_game_hr(NB_PIECES, pieces);
    test_delete_game(g);


 /*   game g1 = new_game_hr(NB_PIECES, pieces);
    printf("Partie A initialisee !\n");

    game g2 = new_game_hr(3, pieces);
    printf("Partie B initialisee !\n\n");

    copy_game(g1,g2); // ici le programme plante, ca deconne au niveau de copy_piece appellee dans copy_game
    //printf("La partie g a bien été copiée dans c");

    printf("La partie g2 avait 3 compte %d pieces.\n\n", game_nb_pieces(g2));

    // ici on determine les parametres du deplacement
    dir d = RIGHT;
    int numpiece = 0;
    int distance = 1;

    //play_move(c, numpiece, d, distance);      // play_move est pas encore terminee dans game.c

    //printf("La piece %d de la partie g2 s'est deplacee de %d case(s).\n", numpiece, distance);



    if (game_over_hr(g2)) {  // pourtant le programme plante
        printf("You win !\n");
        printf("Niveau suivant ?\n\n");
    }

    // Completer la suite


    delete_game(g2);

*/

    return EXIT_SUCCESS;
}
