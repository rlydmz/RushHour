

#include <stdio.h>
#include <stdlib.h>
#include "liste_dc.h"

// Liste DC contenant des game

ListeDC_game *init_list_game(game g){
    ListeDC_game *liste = malloc(sizeof(*liste));
    ListElem_game *element = malloc(sizeof(*element));

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

void insert_first_game(ListeDC_game *liste, game g){
    printf("dans la fonction\n");
    ListElem_game *nouveau = malloc(sizeof(*nouveau));
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

void insert_last_game(ListeDC_game *liste, game g){

    ListElem_game *nouveau = malloc(sizeof(*nouveau));
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

void delete_last_game(ListeDC_game *liste){
    if (liste == NULL){
        fprintf(stderr,"Error: list is null");
        exit(EXIT_FAILURE);
    }

    if (liste->first != NULL){
        ListElem_game *aSupprimer = liste->first;
        liste->first = liste->first->next;
        liste->first->prev = NULL;
        free(aSupprimer);
    }
}

void delete_first_game(ListeDC_game *liste){
    if (liste == NULL){
        fprintf(stderr,"Error: list is null");
        exit(EXIT_FAILURE);
    }

    if (liste->last != NULL){
        ListElem_game *aSupprimer = liste->last;
        liste->last = liste->last->prev;
        liste->last->next = NULL;
        free(aSupprimer);
    }
}

game get_first_game(ListeDC_game *liste){
    if (liste == NULL){
        fprintf(stderr,"Error: list is null");
        exit(EXIT_FAILURE);
    }
    return liste->first->g;
}

game get_last_game(ListeDC_game *liste){
    if (liste == NULL){
        fprintf(stderr,"Error: list is null");
        exit(EXIT_FAILURE);
    }
    return liste->last->g;
}

game get_element_from_first_game(ListeDC_game *liste, int index){
    if(index<0||index>=get_size_gamelist(liste)){
        fprintf(stderr, "Index out of range");
        exit(EXIT_FAILURE);
    }
    if(liste==NULL){
        fprintf(stderr, "Error: list is empty");
        exit(EXIT_FAILURE);
    }
    ListElem_game *current = liste->first;
    int i=0;
    while(i<index){
        current = current->next;
        i++;
    }
    return current->g;

}

game get_element_from_last_game(ListeDC_game *liste, int index){
    if(index<0||index>=get_size_gamelist(liste)){
        fprintf(stderr, "Index out of range");
        exit(EXIT_FAILURE);
    }
    if(liste==NULL){
        fprintf(stderr, "Error: list is empty");
        exit(EXIT_FAILURE);
    }
    ListElem_game *current = liste->last;
    int i=0;
    while(i<index){
        current = current->prev;
        i++;
    }
    return current->g;

}

int get_size_gamelist(ListeDC_game* liste){
    int cpt=0;
    ListElem_game* current = liste->first;
    while(current!=NULL){
        current = current->next;
        cpt++;
    }
    return cpt;
}

bool is_game_inlist(cgame g, ListeDC_game* liste){
    ListElem_game* current = liste->first;
    while(current!=NULL){
        if(equals(current->g,g)) return true;
        current = current->next;
    }
    return false;
}

ListeDC_game* clone_list_game(ListeDC_game* liste){

    ListElem_game *nouveau = liste->first;
    game* newgame = malloc(get_size_gamelist(liste)*sizeof *newgame);
    if(newgame==NULL)
        exit(EXIT_FAILURE);

    for(int i=0;i<get_size_gamelist(liste);i++){
        newgame[i] = new_game(game_width(nouveau->g),game_height(nouveau->g),game_nb_pieces(nouveau->g),game_pieces_copy(nouveau->g));
        nouveau = nouveau->next;
    }

    ListeDC_game* listCpy = init_list_game(newgame[0]);
    for(int i=1;i<get_size_gamelist(liste);i++){
        insert_last_game(listCpy,newgame[i]);
    }

    return listCpy;
}


// Liste DC contenant des listes DC contenant des game

ListeDC_list *init_list_list(ListeDC_game* gamelist){
    ListeDC_list *liste = malloc(sizeof(*liste));
    ListElem_list *element = malloc(sizeof(*element));

    if (liste == NULL || element == NULL){
        fprintf(stderr,"Error: list or element is null");
        exit(EXIT_FAILURE);
    }

    element->liste = gamelist;
    element->next = NULL;
    element->prev = NULL;
    liste->first = element;
    liste->last = element;

    return liste;
}

void insert_last_list(ListeDC_list *liste, ListeDC_game* gamelist){

    ListElem_list *nouveau = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL){
        fprintf(stderr,"Error: list or element is null");
        exit(EXIT_FAILURE);
    }

    nouveau->liste = gamelist;
    nouveau->prev = NULL;
    nouveau->next = liste->first;
    liste->first = nouveau;
    (nouveau->next)->prev = nouveau;
}

void insert_first_list(ListeDC_list *liste, ListeDC_game* gamelist){

    ListElem_list *nouveau = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL){
        fprintf(stderr,"Error: list or element is null");
        exit(EXIT_FAILURE);
    }

    nouveau->liste = gamelist;
    nouveau->next = NULL;
    nouveau->prev = liste->last;
    liste->last = nouveau;
    (nouveau->prev)->next = nouveau;
}

void delete_last_list(ListeDC_list *liste){
    if (liste == NULL){
        fprintf(stderr,"Error: list is null");
        exit(EXIT_FAILURE);
    }

    if (liste->first != NULL){
        ListElem_list *aSupprimer = liste->first;
        liste->first = liste->first->next;
        liste->first->prev = NULL;
        free(aSupprimer);
    }
}

void delete_first_list(ListeDC_list *liste){
    if (liste == NULL){
        fprintf(stderr,"Error: list is null");
        exit(EXIT_FAILURE);
    }

    if (liste->last != NULL){
        ListElem_list *aSupprimer = liste->last;
        liste->last = liste->last->prev;
        liste->last->next = NULL;
        free(aSupprimer);
    }
}

ListeDC_game* get_first_list(ListeDC_list *liste){
    if (liste == NULL){
        fprintf(stderr,"Error: list is null");
        exit(EXIT_FAILURE);
    }
    return liste->first->liste;
}

ListeDC_game* get_last_list(ListeDC_list *liste){
    if (liste == NULL){
        fprintf(stderr,"Error: list is null");
        exit(EXIT_FAILURE);
    }
    return liste->last->liste;
}

ListeDC_game* get_element_from_first_list(ListeDC_list *liste, int index){
    if(index<0||index>=get_size_listlist(liste)){
        fprintf(stderr, "Index out of range");
        exit(EXIT_FAILURE);
    }
    if(liste==NULL){
        fprintf(stderr, "Error: list is empty");
        exit(EXIT_FAILURE);
    }
    ListElem_list *current = liste->first;
    int i=0;
    while(i<index){
        current = current->next;
        i++;
    }
    return current->liste;

}

ListeDC_game* get_element_from_last_list(ListeDC_list *liste, int index){
    if(index<0||index>=get_size_listlist(liste)){
        fprintf(stderr, "Index out of range");
        exit(EXIT_FAILURE);
    }
    if(liste==NULL){
        fprintf(stderr, "Error: list is empty");
        exit(EXIT_FAILURE);
    }
    ListElem_list *current = liste->last;
    int i=0;
    while(i<index){
        current = current->prev;
        i++;
    }
    return current->liste;

}

int get_size_listlist(ListeDC_list* liste){
    int cpt=0;
    ListElem_list* current = liste->first;
    while(current!=NULL){
        current = current->next;
        cpt++;
    }
    return cpt;
}
