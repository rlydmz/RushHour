

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
#define NB_PIECES 3


int main(int argc, char* argv[]){

    // nouveau jeu g

    piece p0 = new_piece(0,3,2,1,true,false);
    piece p1 = new_piece(3,1,1,3,false,true);
    piece p2 = new_piece(2,0,2,1,true,false);
    //piece p3 = new_piece(5,2,1,3,false,true);
    //piece p4 = new_piece(0,1,1,2,false,true);

    piece* pcs = malloc(3*sizeof(piece));
    if(pcs==NULL){
        fprintf(stderr,"Error: allocation failed");
        exit(EXIT_FAILURE);
    }

    pcs[0]=p0;
    pcs[1]=p1;
    pcs[2]=p2;
    //pcs[3]=p3;
    //pcs[4]=p4;


    game g = new_game(GRID_SIZE, GRID_SIZE,3,pcs); // partie initiale
    Fifo* file = initialiser_fifo(); // file pour contenir les noeuds de l'arbre des possibilites
    ListeDC_game* liste = init_list_game(g);
    ListeDC_game* configs = init_list_game(g); // contient un exemplaire de chaque etat deja explore
    ListeDC_list* exploration = init_list_list(liste);
    int cpt=0;

    /* BEGIN ______________________________ */

    printf("\n  == JEU INITIAL ==  \n"); // affichage du jeu initial
    display(g);
    printf("\n =================\n\n");

    enfiler(file,g); // on enfile le jeu initial




    while(!game_over_rh(get_value(file)) && !is_fifo_empty(file)){ /* tant que le premier de la file n'est pas une config gagnante */



        game current = defiler(file);
        int nbIssues = nb_issues(current); // nombre d'issues au jeu courant

        printf("\nTOUR %d - %d ISSUES\nTaille de exploration: %d\n\n",cpt,nbIssues,get_size_listlist(exploration));

        game* issues = get_issues(current);

//        for(int i=0;i<nbIssues;i++){
//            if(game_over_rh(issues[i])){
//                printf("GAME OVER\n");
//                break;
//            }
//        }

        ListElem_list* iter = exploration->first;
        while(!equals(current,iter->liste->last->g)){  // parcours de la liste exploration jusqu'a trouver une liste DC dont le dernier element possede un game identique a current
            iter = iter->next;
        }

        for(int i=0;i<nbIssues-1;i++){ // insertion des copies dans exploration
            insert_last_list(exploration,clone_list_game(iter->liste));
        }

        iter = exploration->first; // on remet l'iterateur a sa valeur initiale
        int i=0;


        while(iter!=NULL){ // insertion des issues en fin des listes DC correspondantes
            if(equals(current,iter->liste->last->g)){

                insert_last_game(iter->liste,issues[i]);
                //display(iter->liste->last->g);
                i++;
            }
            iter = iter->next;
        }

        for(int i=0;i<nbIssues;i++){

            //if(!is_game_inlist(issues[i],configs)){
                //display(issues[i]);
            enfiler(file,issues[i]);
            insert_last_game(configs,issues[i]);
            //}
        }

        cpt++;
        free(iter);

    }


    printf("\n\n     RESULTAT\n");
    display(get_value(file));
    printf("\n Solution trouvee en %d coups\n",cpt);


    /* END _________________________________ */

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


game* get_issues(game g){


    int nbIssues = nb_issues(g); // calcul du nombre d'issues

    game* issues = malloc(nbIssues*sizeof(*issues));
    if(issues==NULL)
        exit(EXIT_FAILURE);

    for(int i=0;i<nbIssues;i++){
        issues[i] = new_game(game_width(g),game_height(g),game_nb_pieces(g),game_pieces_copy(g));
    }

    int i=0;
    int piecenum = 0;

    while(i<nbIssues){

        cpiece current = game_piece(g,piecenum);

        if(can_move_x(current)){
            if(is_move_allowed(g,current,LEFT)){
                play_move(issues[i],piecenum,LEFT,1);
                i++;
            }
            if(is_move_allowed(g,current,RIGHT)){
                play_move(issues[i],piecenum,RIGHT,1);
                i++;
            }
        }
        if(can_move_y(current)){
            if(is_move_allowed(g,current,DOWN)) {
                play_move(issues[i],piecenum,DOWN,1);
                i++;
            }
            if(is_move_allowed(g,current,UP)) {
                play_move(issues[i],piecenum,UP,1);
                i++;
            }
        }
        piecenum ++;
    }
    return issues;
}




