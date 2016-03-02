#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "piece.h"


struct game_s{
    int moves;
    int nb_pieces;
    piece p[];
};


game new_game_hr(int nb_pieces, piece *pieces){
    game g = malloc(sizeof(struct game_s));
    g->moves = 0;
    g->nb_pieces = nb_pieces;
    for (int i=0; i<nb_pieces ;i++){
        g->p[i] = pieces[i];
        copy_piece(g->p[i],pieces[i]);
    }
    return g;
}

void delete_game (game g){
    free(g);
}

/**
 * @brief Clone the game dst into the game dst.
 * @param src the game to copy
 * @param dst the copied game.
 */
void copy_game (cgame src, game dst){
    dst->moves = src->moves;
    dst->nb_pieces = src->nb_pieces;
    for (int i = 0; i<game_nb_pieces(src);i++ ){
        copy_piece(src->p[i],dst->p[i]);
    }
}

/**
 * @brief Return the number of pieces on the game board g
*/
int game_nb_pieces(cgame g){
    return g->nb_pieces;
}


/**
 * @brief Return the piece of g with number bum
 * @param piece_num the num of the piece. This value must be between 0 and game_nb_pieces(g)-1.
*/
cpiece game_piece(cgame g, int piece_num){
    if(piece_num>game_nb_pieces(g))
        fprintf(stderr,"Error, place not in the game");
    return g->p[piece_num];
}


/**
 * @brief Test is the game is over (i.e. if the piece 0 has reached the exit).
 * @return true if the piece number 0 has coordinates (4,3)
*/
bool game_over_hr(cgame g){
    int x = get_x(g->p[0]);
    int y = get_y(g->p[0]);


}


/**
 * @brief Tries to move the piece of number piece_num in direction d for distance cells.
 *
 * If the move is valid, then corresponding piece is moved, the number of moves of the game is incremented by distance and the returned value is true.
 * If the move is not valid, the game g remains unchanged and the function returns false.
 * A move is valid if:
 *   1) the piece stays in the game board,
 *   2) the direction is compatible is the type of the piece,
 *   3) the piece do not cross any other piece during its movement.
 * @param distance length of the move. This value must be strictly positive.
 * @param piece_num the number of the piece to move. This value must be between 0 and game_nb_pieces(g)-1.
 * @return true if the move is valid, false otherwise.
*/
bool play_move(game g, int piece_num, dir d, int distance);

/**
 * @brief Return the number of moves this the beginning of the game g.
 * Remind that move of a single piece of k cells in a single direction counts for k.
 */
int game_nb_moves(cgame g);

