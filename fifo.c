

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "fifo.h"

//________________ IMPLEMENTATION DE LA STRUCTURE FIFO _________________//


// initialise la file
Fifo* initialiser_fifo(){
    Fifo *file = malloc(sizeof(*file));
    file->first = NULL;
    return file;
}

// vrai si la file est vide
bool is_fifo_empty(Fifo* file){
    return(file->first==NULL);
}

// ajoute une valeur a la file
void enfiler(Fifo* file, game newGame){
    FileElem *nouveau = malloc(sizeof(*nouveau));
    if (file == NULL || nouveau == NULL){
        exit(EXIT_FAILURE);
    }
    nouveau->g = newGame;
    nouveau->next = NULL;

    if (!is_fifo_empty(file)){
        FileElem *current = file->first;
        while (current->next != NULL){
            current = current->next;
        }
        current->next = nouveau;
    }
    else{
        file->first = nouveau;
    }

}

// defile et renvoie la valeur sortie du fifo
game defiler(Fifo* file){
    if (file == NULL){
        fprintf(stderr,"Error: fifo is empty");
        exit(EXIT_FAILURE);
    }
    game g = malloc(sizeof(g));
        if(g==NULL){
        fprintf(stderr,"Error: allocation failed");
        exit(EXIT_FAILURE);
    }
    if (file->first != NULL){
        FileElem *elementDefile = file->first;
        g = elementDefile->g;
        file->first = elementDefile->next;
        free(elementDefile);
    }
    return g;
}

// revoie la tete de file sans defiler
game get_value(Fifo* file){
    if (file == NULL){
        fprintf(stderr,"Error: fifo is empty");
        exit(EXIT_FAILURE);
    }
    game g = malloc(sizeof(g));
    if(g==NULL){
        fprintf(stderr,"Error: allocation failed");
        exit(EXIT_FAILURE);
    }
    FileElem* first = file->first;
    g = first->g;
    return g;

}




