

#include <stdio.h>
#include <stdlib.h>
#include "liste_dc.h"



ListeDC *init_list(game g){
    ListeDC *liste = malloc(sizeof(*liste));
    ListElem *element = malloc(sizeof(*element));

    if (liste == NULL || element == NULL){
        fprintf(stderr,"Error: list or element is null");
        exit(EXIT_FAILURE);
    }

    element->g = g;
    element->next = NULL;
    element->prev = NULL;
    liste->first = element;
    liste->last = element;

    return liste;
}

void insert_last(ListeDC *liste, game g){

    ListElem *nouveau = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL){
        fprintf(stderr,"Error: list or element is null");
        exit(EXIT_FAILURE);
    }

    nouveau->g = g;
    nouveau->prev = NULL;
    nouveau->next = liste->first;
    liste->first = nouveau;
    (nouveau->next)->prev = nouveau;
}

void insert_first(ListeDC *liste, game g){

    ListElem *nouveau = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL){
        fprintf(stderr,"Error: list or element is null");
        exit(EXIT_FAILURE);
    }

    nouveau->g = g;
    nouveau->next = NULL;
    nouveau->prev = liste->last;
    liste->last = nouveau;
    (nouveau->prev)->next = nouveau;
}

void delete_last(ListeDC *liste){
    if (liste == NULL){
        fprintf(stderr,"Error: list is null");
        exit(EXIT_FAILURE);
    }

    if (liste->first != NULL){
        ListElem *aSupprimer = liste->first;
        liste->first = liste->first->next;
        liste->first->prev = NULL;
        free(aSupprimer);
    }
}

void delete_first(ListeDC *liste){
    if (liste == NULL){
        fprintf(stderr,"Error: list is null");
        exit(EXIT_FAILURE);
    }

    if (liste->last != NULL){
        ListElem *aSupprimer = liste->last;
        liste->last = liste->last->prev;
        liste->last->next = NULL;
        free(aSupprimer);
    }
}

game get_first(ListeDC *liste){
    if (liste == NULL){
        fprintf(stderr,"Error: list is null");
        exit(EXIT_FAILURE);
    }
    return liste->first->g;
}

game get_last(ListeDC *liste){
    if (liste == NULL){
        fprintf(stderr,"Error: list is null");
        exit(EXIT_FAILURE);
    }
    return liste->last->g;
}

game get_element_from_first(ListeDC *liste, int index){
    if(index<0||index>=get_size(liste)){
        fprintf(stderr, "Index out of range");
        exit(EXIT_FAILURE);
    }
    if(liste==NULL){
        fprintf(stderr, "Error: list is empty");
        exit(EXIT_FAILURE);
    }
    ListElem *current = liste->first;
    int i=0;
    while(i<index){
        current = current->next;
        i++;
    }
    return current->g;

}

game get_element_from_last(ListeDC *liste, int index){
    if(index<0||index>=get_size(liste)){
        fprintf(stderr, "Index out of range");
        exit(EXIT_FAILURE);
    }
    if(liste==NULL){
        fprintf(stderr, "Error: list is empty");
        exit(EXIT_FAILURE);
    }
    ListElem *current = liste->last;
    int i=0;
    while(i<index){
        current = current->prev;
        i++;
    }
    return current->g;

}

int get_size(ListeDC* liste){
    int cpt=0;
    ListElem* current = liste->first;
    while(current!=NULL){
        current = current->next;
        cpt++;
    }
    return cpt;
}

