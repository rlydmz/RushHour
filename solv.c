

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "game.h"
#include "piece.h"
#include "fifo.h"
#include "liste_dc.h"
#include "solv.h"

#define GRID_SIZE 6


int main(int argc, char* argv[]){

    // nouveau jeu g1

    piece p0 = new_piece(0,3,2,1,true,false);
    piece p1 = new_piece(3,1,1,3,false,true);
    piece p2 = new_piece(2,0,2,1,true,false);
    piece p3 = new_piece(5,2,1,3,false,true);

    piece* pcs = malloc(4*sizeof(piece));
    if(pcs==NULL){
        fprintf(stderr,"Error: allocation failed");
        exit(EXIT_FAILURE);
    }

    pcs[0]=p0;
    pcs[1]=p1;
    pcs[2]=p2;
    pcs[3]=p3;

    game g = new_game(GRID_SIZE, GRID_SIZE,4,pcs);
    display(g);
    printf("\n____________________\n\n");

    // begin

    game* issues = get_issues(g);


    printf("Code execute sans plantage\n");

//    while(!game_over_rh(get_first(fref))){ // tant que la tete de la file fref n'est pas une config gagnante
//
//        game current = defiler(fref); // on defile et recupere cette config
//        int nbIssues = nb_issues(current); // calcul du nombre d'issues
//
//    }

    // end


    delete_game(g);
    return EXIT_SUCCESS;
}

// affichage de la config g
void display(cgame g){
    printf("\n");
    for(int j=0;j<GRID_SIZE;j++){
            printf(" %d | ", GRID_SIZE-j-1);
        for(int i=0;i<GRID_SIZE;i++){
            if(game_square_piece((game)g, i,GRID_SIZE-j-1)==-1) printf(".");
            else printf("%d", game_square_piece((game)g, i,GRID_SIZE-j-1));
            printf(" ");
        }
        printf("\n");
    }
    printf("    ");
    for(int k=0;k<GRID_SIZE;k++){
        printf("__");
    }
    printf("\n     ");
    for(int l=0;l<GRID_SIZE;l++){
        printf("%d ",l);
    };

    printf("\n");
}

// vrai si aucune piece ni aucun bord de grille ne bloque le mouvement
bool is_move_allowed(cgame g, cpiece p, dir d){
    if (touch_border(g,p,d)) return false;
    switch (d){
        case UP:
            return(game_square_piece((game)g,get_x(p), get_y(p)+get_height(p)) == -1);
            break;
        case DOWN:
            return (game_square_piece((game)g,get_x(p), get_y(p)-1) == -1);
            break;
        case LEFT:
            return (game_square_piece((game)g, get_x(p)-1, get_y(p)) == -1);
            break;
        case RIGHT:
            return (game_square_piece((game)g,get_x(p)+get_width(p), get_y(p))== -1);
            break;
        default:
            fprintf(stderr, "Direction invalide");
            exit(EXIT_FAILURE);
    }
}

// vrai si la piece p touche le bord de la grille dans la direction d
bool touch_border(cgame g, cpiece p, dir d){
    switch(d){
        case UP:
            return (get_y(p)+get_height(p)== GRID_SIZE);
            break;
        case DOWN:
            return (get_y(p)==0);
            break;
        case LEFT:
            return (get_x(p)==0);
            break;
        case RIGHT:
            return (get_x(p)+get_width(p)==GRID_SIZE);
            break;
        default:
            fprintf(stderr, "Direction invalide");
            exit(EXIT_FAILURE);
    }
}

// renvoie le nombre de configurations possibles a l'issue de la configuration courante
int nb_issues(cgame g){
    int n = 0;
    for(int i=0;i<game_nb_pieces(g);i++){
        cpiece current = game_piece(g,i);
        if(can_move_x(current)){
            if(is_move_allowed(g,current,LEFT)) n++;
            if(is_move_allowed(g,current,RIGHT)) n++;
        }
        if(can_move_y(current)){
            if(is_move_allowed(g,current,DOWN)) n++;
            if(is_move_allowed(g,current,UP)) n++;
        }
    }
    return n;
}

Fifo** clone_fifo(Fifo** farray, int nbClones){
    int fsize = sizeof(Fifo);

    farray = realloc(farray,nbClones*sizeof(*farray));
    if(farray==NULL){
        fprintf(stderr,"Error: reallocation failed");
        exit(EXIT_FAILURE);
    }

    for(int i=1;i<nbClones;i++){
        farray[i] = malloc(sizeof(*farray[i]));
        farray[i] = memcpy(farray[i],farray[0],fsize);
    }
    return farray;

}

game* get_issues(game g){


    int nbIssues = nb_issues(g); // calcul du nombre d'issues

    game* issues = malloc(nbIssues*sizeof(*issues));
    if(issues==NULL)
        exit(EXIT_FAILURE);

    for(int i=0;i<nbIssues;i++){
        issues[i] = new_game(g->width,g->height,g->nb_pieces,g->p);
        printf("adresse issues[%d]->nb_pieces: %p\n", i,(issues[i]->nb_pieces));
    }

    int i=0;
    int piecenum = 0;

    while(i<nbIssues){

        cpiece current = game_piece(g,piecenum);

        if(can_move_x(current)){
            if(is_move_allowed(g,current,LEFT)){
                printf("Avant le de bouger la piece %d\n",i);
                display(g);
                play_move(issues[i],piecenum,LEFT,1);
                printf("Et juste apres\n");
                display(g);
                display(issues[i]);
                i++;
            }
            if(is_move_allowed(g,current,RIGHT)){
                printf("Avant le de bouger la piece %d\n",i);
                display(g);
                play_move(issues[i],piecenum,RIGHT,1);
                printf("Et juste apres\n");
                display(g);
                display(issues[i]);
                i++;
            }
        }
        if(can_move_y(current)){
            if(is_move_allowed(g,current,DOWN)) {
                printf("Avant le de bouger la piece %d\n",i);
                display(g);
                play_move(issues[i],piecenum,DOWN,1);
                printf("Et juste apres\n");
                display(g);
                display(issues[i]);
                i++;
            }
            if(is_move_allowed(g,current,UP)) {
                printf("Avant le de bouger la piece %d\n",i);
                display(g);
                play_move(issues[i],piecenum,UP,1);
                printf("Et juste apres\n");
                display(g);
                display(issues[i]);
                i++;
            }
        }
        piecenum ++;
    }
    return issues;
}




