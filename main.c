#include "piece.h"
#include "game.h"
#include "mygame.h"
#include "stdbool.h"
#include "stdlib.h"
#include "stdio.h"

#define TAILLE 6

void afficher_game(game g){
    cpiece piece_tmp = game_piece(g,0);
    int grille[TAILLE][TAILLE];

    for (int i=0;i<TAILLE; i++){
        for (int j=0; j<TAILLE ; j++){
            grille[i][j]= -1;
            printf("%d",grille[i][j]);
        }
        printf("\n");
    }

    for (int j=0; j<game_nb_pieces(g) ;j++ ){
        for (int i=0;i<get_width(game_piece(g,i)) ;i++ ){
            if(is_horizontal(game_piece(g,i))){
                grille[i][j] = i;
                printf("%d",grille[i][j]);
            }
        }
    }










}


piece* creer_piece_game(){
    piece *tabP= (piece*)malloc(sizeof(piece));
    tabP[0] = new_piece_rh(3,0,true,true);
    tabP[1] = new_piece_rh(2,5,false,false);
    tabP[2] = new_piece_rh(1,2,true,true);
    tabP[3] = new_piece_rh(5,3,false,true);
    tabP[4] = new_piece_rh(2,3,false,false);
    tabP[5] = new_piece_rh(2,0,false,true);

 return tabP;
}





int main(int argc, char* argv[]){

game g= new_game_hr(6,creer_piece_game()); //création du jeu
afficher_game(g);








return 0;

}
