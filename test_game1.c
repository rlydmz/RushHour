#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "piece.h"

/**Retourne true si le jeu à le nombre x de piece, sinon false**/
bool test_game_nb_pieces(game g, int nbPieces){
    if(game_nb_pieces(g) == nbPieces)
        return true;
    return false;
}

/**Retourne true si les pièces à l'indice num_piece sont identiques, sinon false**/
bool test_game_piece(game g, int num_piece, int x, int y){
  cpiece pieceTest = game_piece((cgame)g, num_piece);
  if((get_x((piece)pieceTest) == x) && (get_y((piece)pieceTest) == y))
    return true;
  return false;
}

/** Cree et initialise les pieces du jeu **/
piece* setup_piece(){
    piece *tabP= (piece*)malloc(sizeof(piece));
    tabP[0] = new_piece_rh(0,3,true,true);
    tabP[1] = new_piece_rh(2,1,true,true);
    tabP[2] = new_piece_rh(3,5,false,true);
    tabP[3] = new_piece_rh(0,2,false,true);
 return tabP;
}

/**Retourne true si le jeu g est égal à la copie de g, sinon false**/
bool test_copy_game(game g)
{
    game gameTmp = (game)malloc(sizeof(game));
    copy_game(g,gameTmp);
    if((game_nb_moves(gameTmp))== (game_nb_moves(g)))
    {
        if((game_nb_pieces(gameTmp))==(game_nb_pieces(g)))
    {
        for (int i=0; i<game_nb_pieces(g) ; i++ )
            {
                if(get_x(game_piece(g,i))==get_x(game_piece(gameTmp,i)) && get_y(game_piece(g,i))==get_y(game_piece(gameTmp,i)))
                    return true;
            }

        }
    }
    return false;
}

/**Retourne true si les coordonnees de sorties sont bien atteintes, faux sinon **/
bool test_game_over_hr(cgame g){
    int x = get_x(game_piece(g,0));
    int y = get_y(game_piece(g,0));
    if(x==4 && y==3)
        return true;
    else
        return false;

}

/** Retourne true si le mouvement a bien été effectué, false sinon **/
bool test_play_move(game g, dir d){

    if(play_move(g,0,d,4)==true)
        return true;
    return false;

}

int main(int argc, char *argv[]){

    bool result = true;
    piece *tabPieces = setup_piece();
    game g = new_game_hr(4,tabPieces);
    result = result && test_game_nb_pieces(g,4);
    result = result && test_game_piece(g,0,0,3);
    result = result && test_play_move(g,RIGHT);
    result = result && test_game_over_hr(g);
    if(result == true)
        printf("Youpi !");

}

