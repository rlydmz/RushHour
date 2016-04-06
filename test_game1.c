#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "piece.h"

/**
 * @brief test if value is equal to expected; if not, displays an error message containing msg to standard error output
 * @return true if expected==value
 */
bool test_equality_int(int expected, int value, char * msg) {
    if (expected != value)
        fprintf(stderr,"ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
    return expected == value;
}

/**
 * @brief test if value is equal to expected; if not, displays an error message containing msg to standard error output
 */
bool test_equality_bool(bool expected, bool value, char * msg) {
    if (expected != value)
        fprintf(stderr,"ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
    return expected == value;
}

/** Cree et initialise les pieces du jeu RushHour**/
piece* setup_piece_hr() {
    piece *tabP= (piece*)malloc(4*sizeof(piece));
    tabP[0] = new_piece_rh(0,3,true,true);
    tabP[1] = new_piece_rh(2,1,true,true);
    tabP[2] = new_piece_rh(3,5,false,true);
    tabP[3] = new_piece_rh(0,2,false,true);
    return tabP;
}


/** Cree et initialise les pieces du jeu RushHourde l'Ane Rouge**/
piece* setup_piece_ane() {
    piece *tabP= (piece*)malloc(4*sizeof(piece));
    tabP[0] = new_piece(1,3,2,2,true,true);
    tabP[1] = new_piece(0,1,1,2,true,true);
    tabP[2] = new_piece(0,0,1,1,true,true);
    tabP[3] = new_piece(3,0,1,1,true,true);
    return tabP;
    }

/**Retourne true si le jeu à le nombre x de piece, sinon false**/
bool test_game_nb_pieces(game g, int nbPieces) {
  bool result = true;
  result = result && test_equality_int(game_nb_pieces(g), nbPieces, "game_nb_pieces");
  return result;
}

/**Retourne true si les pièces à l'indice num_piece sont identiques, sinon false**/
bool test_game_piece(game g, int num_piece, int x, int y) {
  bool result = true;
    cpiece pieceTest = game_piece((cgame)g, num_piece);
    result = result && test_equality_int(get_x((piece)pieceTest), x, "get_x");
    result = result && test_equality_int(get_y((piece)pieceTest), y, "get_y");
    return result;
}

/**Retourne true si le jeu g est égal à la copie de g, sinon false**/
bool test_copy_game(game g)
{
  bool result = true;
    game gameTmp = (game)malloc(sizeof(game));
    copy_game(g,gameTmp);
    result = result && test_equality_int(game_nb_moves(gameTmp), game_nb_moves(g), "game_nb_moves");
    result = result && test_equality_int(game_nb_pieces(gameTmp), game_nb_pieces(g), "game_nb_pieces");
    for (int i=0; i<game_nb_pieces(g) ; i++ )
            {
	      result = result && test_equality_int(get_x(game_piece(g,i)), get_x(game_piece(gameTmp,i)), "get_x");
	      result = result && test_equality_int(get_y(game_piece(g,i)), get_y(game_piece(gameTmp,i)), "get_y");
            }
    return result;
}

/**Retourne true si les coordonnees de sorties sont bien atteintes, faux sinon **/
bool test_game_over_hr(cgame g) {

  bool result = true;
  result = result && test_equality_int(get_x(game_piece(g,0)), 4, "get_x");
  result = result && test_equality_int(get_y(game_piece(g,0)), 3, "get_y");
  return result;

}

/**Retourne true si les coordonnees de sorties sont bien atteintes, faux sinon **/
bool test_game_over_ane(cgame g) {

  bool result = true;
  result = result && test_equality_int(get_x(game_piece(g,0)), 0, "get_x");
  result = result && test_equality_int(get_y(game_piece(g,0)), 1, "get_y");
  return result;

}

/** Retourne true si le mouvement a bien été effectué, false sinon **/
bool test_play_move_hr(game g, dir d) {

    if(play_move(g,0,d,4)==true)
        return true;
    return false;

}

/** Retourne true si le mouvement a bien été effectué, false sinon **/
bool test_play_move_ane(game g, dir d) {

    if(play_move(g,0,d,3)==true)
        return true;
    return false;

}

int main(int argc, char *argv[]) {

    bool result = true;
    piece *tabPiecesHR = setup_piece_hr();
    game gHR = new_game(6,6,4,tabPiecesHR);
    /*
    piece *tabPiecesANE = setup_piece_ane();
    game gANE = new_game(4,5,4,tabPiecesANE);
    */

   
    result = result && test_equality_bool(true, test_game_nb_pieces(gHR,4), "game_nb_pieces");
    result = result && test_equality_bool(true, test_game_piece(gHR,0,0,3), "game_piece");
    result = result && test_equality_bool(true, test_play_move_hr(gHR,RIGHT), "play_move_hr");
    result = result && test_equality_bool(true, test_game_over_hr(gHR), "game_over_hr");
  

    //result = result && test_equality_bool(true, test_play_move_ane(gANE,DOWN), "play_move_ane");
    //result = result && test_equality_bool(true, test_game_over_ane(gANE), "game_over_ane");
       

    //delete_game(gHR);
    //delete_game(gANE);
    
    if(result == true)
        printf("Youpi ! \n");

}

