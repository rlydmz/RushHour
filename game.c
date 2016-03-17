#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "piece.h"


struct game_s{
    int moves;
    int width;      /**Largeur du jeu**/
    int height;     /**Hauteur du jeu**/
    int nb_pieces;
    piece p[];

};


game new_game (int width, int height, int nb_pieces, piece *pieces){
    game g = (game)malloc(sizeof(struct game_s));
    g->moves = 0;
    g->width = width;
    g->height = height;
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
    if(x<0 || x>(g->width)-1 || y<0 || y>(g->height)-1) return -1; // carre hors de la grille

    int num_piece = -1;                 // variable de retour


    for(int i=0 ; i<(g->nb_pieces);i++){// on teste toutes les pieces du jeu
        piece tmpPiece = (piece)game_piece(g,i);
        int tmpX = get_x(tmpPiece);
        int tmpY = get_y(tmpPiece);

        for (int j = tmpX; j<=get_width(tmpPiece)-1+tmpX ; j++ ){        // on avance sur la prochaine case de la pièce sur l'axe x
            if(j == x){
                for(int k=tmpY; k<=get_height(tmpPiece)-1+tmpY; k++){   // on avance sur la prochaine case de la pièce sur l'axe y
                    if(k == y)
                        num_piece = i;  // si j==x et k==y on stocke le numéro de la pièce dans num_piece
                }
            }
	}
    }

    return num_piece;

}

game new_game_hr(int nb_pieces, piece *pieces){
  game g = (game)malloc(sizeof(struct game_s));
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
    return (cpiece)g->p[piece_num];
}

bool game_over_hr(cgame g){
    int x = get_x(g->p[0]);
    int y = get_y(g->p[0]);
    if(x==4 && y==3)
        return true;
    else
        return false;

}

bool play_move(game g, int piece_num, dir d, int distance){

    if (distance<=0 || piece_num<0 || piece_num>game_nb_pieces(g)-1 )
    {
        printf("Erreur lors du mouvement \n");
        return false;
    }
    int dis=distance;
    dir dir_op;
    while (dis!=0)
    {
        dis --;
        move_piece((piece)game_piece(g,piece_num),d,1);
        for(int i=0; i<game_nb_pieces(g); i++)
        {
            if(i==piece_num)
            {
                continue;
            }
            if (intersect(game_piece(g,piece_num),game_piece(g,i)) ||
            	get_x((piece)game_piece(g,piece_num)) > (6-get_width((piece)game_piece(g,piece_num))) ||
                get_y((piece)game_piece(g,piece_num)) > (6-get_height((piece)game_piece(g,piece_num))) ||
                get_x((piece)game_piece(g,piece_num)) < 0 || get_y((piece)game_piece(g,piece_num)) < 0)
            {
                if(d == LEFT)
                {
                    dir_op = RIGHT;
                }
                if(d == RIGHT)
                {
                    dir_op = LEFT;
                }
                if(d == UP)
                {
                    dir_op = DOWN;
                }
                if(d == DOWN)
                {
                    dir_op = UP;
                }
                move_piece((piece)game_piece(g,piece_num),dir_op,distance-dis);
                return false;
            }
        }
    }
    (*g).moves+=distance;
    return true;
}

int game_nb_moves(cgame g){
    return g->moves;
}
