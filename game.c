
#ifndef _GAME_H_
#define _GAME_H_
#include <stdbool.h>
#include "piece.h"

typedef struct game_s{
    int width;
    int height;
    int moves;
    int nb_pieces;
    piece p[];
};

void delete_game (game g){
    if(g!=NULL)
        free(g);
}

void copy_game (cgame src, game dst){
    dst->moves = src->moves;
    dst->nb_pieces = src->nb_pieces;
    for (int i = 0; i<game_nb_pieces(src);i++ ){
        copy_piece(src->p[i],dst->p[i]);
    }
}

int game_nb_pieces(cgame g){
    return g->nb_pieces;
}

cpiece game_piece(cgame g, int piece_num){
    if(piece_num>game_nb_pieces(g))
        fprintf(stderr,"Error, place not in the game");
    return g->p[piece_num];
}

bool game_over_hr(cgame g){
    int x = get_x(g->p[0]);
    int y = get_y(g->p[0]);
    if(x==4 && y==3)
        return true;
    else
        return false;

}

//bool play_move(game g, int piece_num, dir d, int distance){
//    piece p2 = new_piece_rh(10,10,true,true);
//    copy_piece(g->p[piece_num],p2);
//
//
//    /**si le mouvement fait sortir la piece**/
//    if(get_x(g->p[0])+distance > 6)
//        fprintf(stderr,"Out of bounds");
//
//    /**direction mauvaise pour mouvement**/
//    if(is_horizontal(g->p[piece_num])){
//        if(d!=LEFT || d!=RIGHT)
//            return false;
//
//    /****/
//    int j = 1;
//    for(int i = 0; i < (g->nb_pieces) && (j<=distance) ;i++){
//        p2->x += j;
//        intersect(p2,g->p[i]);
//        j++;
//    }
//    }
//    else if(!is_horizontal(g->p[piece_num])){
//        if(d!=UP || d!=DOWN)
//            return false;
//    }
//
//
//}

int game_nb_moves(cgame g){
    return g->moves;
}



///////////// version 2 /////////////////

game new_game (int width, int height, int nb_pieces, piece *pieces){
    game g = malloc(sizeof(struct game_s));
    g->width = width;
    g->height = height;
    g->moves = 0;
    g->nb_pieces = nb_pieces;
    for (int i=0; i<nb_pieces ;i++){
        g->p[i] = pieces[i];
        copy_piece(g->p[i],pieces[i]);
    }
    return g;
}

int game_width(cgame g){
    return g->width;
}

int game_height(cgame g){
    return g->height;
}

int game_square_piece (game g, int x, int y){
    if(x<0 || x>(g->witdth)-1 || y<0 || y>(g->height)-1) return -1; // carre hors de la grille

    int num_piece = -1; // variable de retour
    for(int i=0 ; i<(g->nb_pieces);i++){ // on teste toutes les pieces du jeu
        if(get_x(game_piece(g,i))<x || get_y(game_piece(g,i))<y) continue; // carre a gauche ou en dessous de la piece i
        // carre au dessus de la piece ou a droite de la piece i sans intersect
        else if(x > get_x(game_piece(g,i))+get_width(game_piece(g,i)) || y > get_y(game_piece(g,i))+get_height(game_piece(g,i))) continue;
        else num_piece = i; // seul cas restant, le carre est sur la piece i (et donc sur aucune autre piece)
    }

    return num_piece;
}


