#include "piece.h"
#include "game.h"
#include "stdbool.h"
#include "stdlib.h"
#include "stdio.h"
#include <string.h>

#define NB_PIECE 10


bool game_over_ane(cgame g){
  int x = get_x(game_piece(g,0));
  int y = get_y(game_piece(g,0));
    if(x==1 && y==0)
        return true;
    else
        return false;

}

void afficher_game(game g) {
    int nbP = game_nb_pieces(g);
    int grille[game_width(g)][game_height(g)];
    /**Mettre toutes les cases de la grille à -1**/

    //intervertir game_height et width
    for (int i=0; i<game_height(g); i++) {
        for (int j=0; j<game_width(g); j++) {
            grille[j][i]= -1;

        }
    }



    printf("\n");
    /**Place l'indice des pièces (dans le tableau de piece de g) dans la grille**/
    int x = 0;
    int y = 0;
    for(int i=0; i<nbP; i++) {
        //cpiece tmp_piece = game_piece(g,i);
        x = get_x(game_piece(g,i));
        y = get_y(game_piece(g,i));

        /*Si la piece est carré 2*2*/
        if(get_width(game_piece(g,i))==2 && get_height(game_piece(g,i))==2) {
            grille[x][y] = i;
            grille[x][y+1] = i;
            grille[x+1][y] = i;
            grille[x+1][y+1] = i;

        }
        else
            /*Si la piece est verticale 1*2*/
            if(get_width(game_piece(g,i))==1 && get_height(game_piece(g,i))==2) {
                for(int j=0; j<get_height(game_piece(g,i)); j++)
                    grille[x][y+j] = i;
            }
            else
                /*Si la piece est horizontale 1*2*/
                if(get_width(game_piece(g,i))==2 && get_height(game_piece(g,i))==1) {
                    for(int j=0; j<get_width(game_piece(g,i)); j++)
                        grille[x+j][y] = i;
                }
                else if(get_width(game_piece(g,i))==1 && get_height(game_piece(g,i))==1)
                    grille[x][y] = i;
    }



    /**AFFICHAGE GRILLE**/

    printf("    ***ANE ROUGE***\n");
    printf("  -  ---------------  -\n");

    for(int ytab=game_height(g)-1; ytab>=0; ytab--) {
        printf("%d # ",ytab);
        for(int xtab=0; xtab<game_width(g); xtab++) {
            printf("|");
            if(grille[xtab][ytab]==-1) /**Si la valeur dans la matrice est -1 on affiche rien**/
                printf("   ");
            else
                printf(" %d ", grille[xtab][ytab]); /**Sinon on affiche le numéro de la pièce présente**/

        }
        printf("| # \n");
    }
    printf("  -  ------EXIT-----  -\n");
    printf("  ");
    printf("    0   1   2   3");
    printf("\n");
    printf("\n");
}


piece* creer_piece_game() {
    piece *tabP= (piece*)malloc(NB_PIECE * sizeof(piece));
    tabP[0] = new_piece(1,3,2,2,true,true);
    tabP[1] = new_piece(0,0,1,1,true,true);
    tabP[2] = new_piece(0,1,1,2,true,true);
    tabP[3] = new_piece(0,3,1,2,true,true);
    tabP[4] = new_piece(1,2,2,1,true,true);
    tabP[5] = new_piece(1,1,1,1,true,true);
    tabP[6] = new_piece(2,1,1,1,true,true);
    tabP[7] = new_piece(3,3,1,2,true,true);
    tabP[8] = new_piece(3,1,1,2,true,true);
    tabP[9] = new_piece(3,0,1,1,true,true);
    return tabP;
}

void debut_jeu(game g) {

    /**Declararion des variables permettant de récupérer et traiter les informations
    destinées aux mouvements des pièces**/
    char numPiece[3];
    char chaineDistance[3];
    char chaineDirection[10];
    int distance = 0;
    int indicePiece = 0;
    dir direction;

    /*Début du jeu. Tant que le jeu n'est pas finis, on continue a demander des informations
    a l'utilisateur*/
    while(!game_over_ane(g)) {

        /* On demande à l'utilisateur de saisir un numéro de pièce */
        printf("Veuillez choisir le numero de la piece a bouger (entre 0 et 9) : ");
        fgets(numPiece,3,stdin);

        /* Si l'indice de la pièce est inférieur à 0 et que la pièce n'existe pas
        On lui renvoie un message d'erreur en l'invitant à recommencer sa saisie */

        if(atoi(numPiece)<0) {
            printf("Cette piece n'existe pas : numero trop petit ! Veuillez reessayer... \n");
            continue;
        }

        /* Si l'indice de la pièce est inférieur supérieur à 6, soit la taille du jeu
        et que la pièce n'existe pas, on lui renvoie un message d'erreur en l'invitant à recommencer sa saisie */

        else if(atoi(numPiece)>NB_PIECE) {
            printf("Cette piece n'existe pas : numero trop grand ! Veuillez reessayer... \n");
            continue;
        }

        /*On regarde si la piece que l'utilisateur a choisi de bouger est horizontale ou verticale
        et on lui propos en fonction les deux directions possible pour le mouvement */

        indicePiece = atoi(numPiece);
        printf("Veuillez choisir une direction : left, right, up, down : ");


        /** On récupère ainsi la direction du mouvement **/
        fgets(chaineDirection,10,stdin);
        if (strcmp(chaineDirection,"left\n")==0 ) {
            direction=LEFT;
        }
        else if (strcmp(chaineDirection,"right\n")==0 ) {
            direction=RIGHT;
        }
        else if (strcmp(chaineDirection,"up\n")==0 ) {
            direction=UP;
        }
        else if (strcmp(chaineDirection,"down\n")==0 ) {
            direction=DOWN;
        }
        /* On récupère la distance du mouvement */
        printf("Veuillez choisir la distance du mouvement a effectuer : ");
        fgets(chaineDistance,3,stdin);
        distance = atoi(chaineDistance);
        /** Si le mouvement est incorrect, on le signiefie **/
        if(play_move(g,indicePiece,direction,distance)==false) {
            printf("Erreur lors de la tentative de mouvement \n");
        }

        printf("------------------------------------------------- \n");
        /** Et on affiche de nouveau la grille après mouvement **/
        afficher_game(g);
    }

    printf("Felicitation, vous avez gagne en %d coups ! \n", game_nb_moves(g));
    printf("------------------------------------------------- \n");
}


int main() {

    game g = new_game(4,5,NB_PIECE,creer_piece_game()); //création du jeu
    afficher_game(g);
    debut_jeu(g);

    return 0;

}
