#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "piece.h"

struct game{
  piece pieces[nbPieces];
  int nbMoves;
  int nbPieces;
};

struct cgame{
  piece pieces[nbPieces];
  int nbMoves;
  int nbPieces;
};

game new_game_hr (int nb_pieces, piece *pieces){
  game g = malloc(sizeof(game));
  if(g==NULL){
    fprintf(stderr,"erreur malloc game\n");
    exit(1);
  }
  g->nbPieces = nb_pieces;
  g->nbMoves = 0;
  g->pieces = pieces;
  return g;
}

void delete_game(game g){
  if(g!=NULL)
    free(g);
}

void copy_game (cgame src, game dst){
  if(src!=NULL){
    for(int i=0;i<src.nbPieces;i++)
      dst.pieces[i]=src.pieces[i];
    dst.nbMoves = src.nbMoves;
    dst.nbPieces = src.nbPieces;
  }
}

int game_nb_pieces(cgame g){
  return(g->nbPieces);
}

piece game_piece(cgame g, int piece_num){
  return(g.pieces[piece_num]);
}

bool game_over_hr(cgame g)
  return((g.pieces[0].x == 4)&&(g.pieces[0].y == 3));
}

bool play_move(game g, int piece_num, dir d, int distance){

  if(intersection){ // condition invalide ___ il faut appeller la fonction intersec() pour CHAQUE AUTRE piece
    return false;
  }
  else if((dir=UP||dir=DOWN)&& g.pieces[piece_num].bougeHorizontalement){ // si direction incompatible
    return false;
  }
  else if((dir=LEFT||dir=RIGHT)&&!(g.pieces[piece_num].bougeHorizontalement)){ // idem pour l'autre axe
    return false;
  }
  else if(dir=LEFT && distance>g.pieces[piece_num].x){ // si la piece sort de la grille par la gauche
    return false;
  }
  else if(dir=DOWN && distance>g.pieces[piece_num].y){ // si la piece sort de la grille par le bas
    return false;
  }
  else if(dir=RIGHT){  // si la piece sort de la grille par la droite
    //et que c'est une petite piece
    if(distance>g.pieces[piece_num].estPetite && distance>4-distance>g.pieces[piece_num].x)
      return false;
    // et que c'est une grande piece
    else if(!(distance>g.pieces[piece_num].estPetite) && distance>3-distance>g.pieces[piece_num].x)
      return false;
  }
  else if(dir=UP){  // si la piece sort de la grille par le haut
    //et que c'est une petite piece
    if(distance>g.pieces[piece_num].estPetite && distance>4-distance>g.pieces[piece_num].y)
      return false;
    // et que c'est une grande piece
    else if(!(distance>g.pieces[piece_num].estPetite) && distance>3-distance>g.pieces[piece_num].y)
      return false;
  }

  // il ne reste plus que les cas ou ca fonctionne on peut donc bouger la piece

    move_piece(g.pieces[piece_num],d,distance);
    g.nbMoves+=distance;
    
    return true;
    
  }
}
    
