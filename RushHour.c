#include "piece.h"
#include "game.h"
#include "stdbool.h"
#include "stdlib.h"
#include "stdio.h"
#include <string.h>

#define TAILLE 6

/** afficher_game affiche la grille de jeu. Le jeu est représenté de la manière suivante :
    -La grille est affichée grâce à des cases
    -A l'intérieur de ces cases peut se trouver soit des voitures, numérotées de 0 (voiture rouge) à TAILLE-1 **/

void afficher_game(game g) {
    int nbP = game_nb_pieces(g);
    int grille[TAILLE][TAILLE];
    /**Mettre toutes les cases de la grille à -1**/
    for (int i=0; i<TAILLE; i++) {
        for (int j=0; j<TAILLE; j++) {
            grille[j][i]= -1;
        }
    }
    printf("\n");
    /**Place l'indice des pièces (dans le tableau de piece de g) dans la grille**/
    for(int i=0; i<nbP; i++) {
        cpiece tmp_piece = game_piece(g,i);
        int x = get_x(tmp_piece);
        int y = get_y(tmp_piece);
        /**On place le numéro de la pièce à l'horizontal dasn les cases**/
        if(is_horizontal(tmp_piece))
            for(int j=0; j<get_width(tmp_piece); j++)
                grille[x+j][y] = i;
        /**On place le numéro de la pièce à la verticale dans les cases**/
        else
            for(int j=0; j<get_height(tmp_piece); j++)
                grille[x][y+j] = i;
    }
    /**AFFICHAGE GRILLE**/
    printf("********RUSHHOUR*********\n");
    for(int ytab=TAILLE-1; ytab>=0; ytab--) {
        printf("%d ",ytab);
        for(int xtab=0; xtab<TAILLE; xtab++) {
            printf("|");
            if(grille[xtab][ytab]==-1) /**Si la valeur dans la matrice est -1 on affiche rien**/
                printf("  ");
            else
                printf(" %d", grille[xtab][ytab]); /**Sinon on affiche le numéro de la pièce présente**/
            if(xtab==5 && ytab==3)
                printf("==>"); /**Affichage de la sortie sous forme d'accolade**/
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("  -----------------------\n");
    printf("  ");
    for(int i=0; i<TAILLE; i++) printf("  %d ",i);
    printf("\n");
    printf("\n");
}

/** creer_piece_game va créer et renvoyer un tableau de pieces
    Les pieces sont pour le moment crées de manière manuelle mais permettent au jeu
    d'être fonctionnel tout en assurant une certaines compléxité **/

piece* creer_piece_game() {
    piece *tabP= (piece*)malloc(TAILLE*sizeof(piece));
    tabP[0] = new_piece_rh(0,3,true,true);
    tabP[1] = new_piece_rh(5,2,false,false);
    tabP[2] = new_piece_rh(2,1,true,true);
    tabP[3] = new_piece_rh(3,5,false,true);
    tabP[4] = new_piece_rh(3,2,false,false);
    tabP[5] = new_piece_rh(0,2,false,true);

    return tabP;
}

/** La fonction début_jeu va permettre au jeu g qui lui est passé en paramètre de fonctionner.
    C'est à dire qu'elle va demander à l'utilisateur de saisir les informations liées aux déplacements
    Des pièces du jeu, effectuera les vérifications nécessaires pour afficher de nouveau le jeu.
    Tant que le jeu n'est pas finis, debut_jeu n'est pas censé s'arreter **/

void debut_jeu(game g, int nbPiece) {

    /**Declararion des variables permettant de récupérer et traiter les informations
    destinées aux mouvements des pièces**/
    char numPiece[3];
    char chaineDistance[3];
    char chaineDirection[10];
    int distance = 0;
    int indicePiece = 0;
    bool estHorizontale;
    dir direction;

    /**Début du jeu. Tant que le jeu n'est pas finit, on continue a demander des informations
    a l'utilisateur**/
    while(!game_over_hr(g)) {

        /** On demande à l'utilisateur de saisir un numéro de pièce **/
        printf("Veuillez choisir le numero de la piece a bouger (entre 0 et 5) : ");
        fgets(numPiece,3,stdin);
        /** Si l'indice de la pièce est inférieur à 0 et que la pièce n'existe pas
        On lui renvoie un message d'erreur en l'invitant à recommencer sa saisie **/
        if(atoi(numPiece)<0) {
            printf("Cette piece n'existe pas : numero trop petit ! Veuillez reessayer... \n");
            continue;
        }
        /** Si l'indice de la pièce est inférieur supérieur à 6, soit la taille du jeu
        et que la pièce n'existe pas, on lui renvoie un message d'erreur en l'invitant à recommencer sa saisie **/
        else if(atoi(numPiece)>nbPiece) {
            printf("Cette piece n'existe pas : numero trop grand ! Veuillez reessayer... \n");
            continue;
        }
        /**On regarde si la piece que l'utilisateur a choisi de bouger est horizontale ou verticale
        et on lui propos en fonction les deux directions possible pour le mouvement **/
        indicePiece = atoi(numPiece);
        if(is_horizontal(game_piece(g,indicePiece))) {
            printf("Veuillez choisir une direction : left ou right : ");
            estHorizontale = true;
        }
        else {
            printf("Veuillez choisir une direction : up ou down : ");
            estHorizontale = false;
        }
        /** On récupère ainsi la direction du mouvement **/
        fgets(chaineDirection,10,stdin);
        if (strcmp(chaineDirection,"left\n")==0 && estHorizontale) {
            direction=LEFT;
        }
        else if (strcmp(chaineDirection,"right\n")==0 && estHorizontale) {
            direction=RIGHT;
        }
        else if (strcmp(chaineDirection,"up\n")==0 && !estHorizontale) {
            direction=UP;
        }
        else if (strcmp(chaineDirection,"down\n")==0 && !estHorizontale) {
            direction=DOWN;
        }
        /** On récupère la distance du mouvement **/
        printf("Veuillez choisir la distance du mouvement a effectuer : ");
        fgets(chaineDistance,3,stdin);
        distance = atoi(chaineDistance);
        /** Si le mouvement est incorrect, on le signifie **/
        if(play_move(g,indicePiece,direction,distance)==false) {
            printf("Erreur lors de la tentive de mouvement \n");
        }

        printf("------------------------------------------------- \n");
        /** Et on affiche de nouveau la grille après mouvement **/
        afficher_game(g);
    }

    printf("Felicitation, vous avez gagne en %d coups ! \n", game_nb_moves(g));
    printf("------------------------------------------------- \n");
}


int main(int argc, char* argv[]) {

    /** Création du jeu **/
    game g = new_game_hr(TAILLE,creer_piece_game());
    /** Affichage du jeu et de la grille de départ **/
    afficher_game(g);
    /** Appel de la fonction de début du jeu **/
    debut_jeu(g,TAILLE);

    return 0;

}
