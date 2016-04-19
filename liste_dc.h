
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"

typedef struct ListElem_game ListElem_game;
typedef struct ListElem_list ListElem_list;
typedef struct ListeDC_game ListeDC_game;
typedef struct ListeDC_list ListeDC_list;

struct ListeDC_game{
    ListElem_game *first;
    ListElem_game *last;
};


struct ListeDC_list{
    ListElem_list *first;
    ListElem_list *last;
};


struct ListElem_game{
    game g;
    ListElem_game *next;
    ListElem_game *prev;
};


struct ListElem_list{
    ListeDC_game* liste;
    ListElem_list *next;
    ListElem_list *prev;

};

// Liste DC contenant des game

ListeDC_game *init_list_game(game g);
void insert_first_game(ListeDC_game *liste, game g);
void insert_last_game(ListeDC_game *liste, game g);
void delete_first_game(ListeDC_game *liste);
void delete_last_game(ListeDC_game *liste);
game get_first_game(ListeDC_game *liste);
game get_last_game(ListeDC_game *liste);
game get_element_from_first_game(ListeDC_game *liste, int index);
game get_element_from_last_game(ListeDC_game *liste, int index);
int get_size_gamelist(ListeDC_game* liste);
bool is_game_inlist(cgame g, ListeDC_game* liste);
ListeDC_game* clone_list_game(ListeDC_game* liste);


// Liste DC contenant des listes DC contenant des game

ListeDC_list *init_list_list(ListeDC_game* liste);
void insert_first_list(ListeDC_list *liste, ListeDC_game* gamelist);
void insert_last_list(ListeDC_list *liste, ListeDC_game* gamelist);
void delete_first_list(ListeDC_list *liste);
void delete_last_list(ListeDC_list *liste);
ListeDC_game* get_first_list(ListeDC_list *liste);
ListeDC_game* get_last_list(ListeDC_list *liste);
ListeDC_game* get_element_from_first_list(ListeDC_list *liste, int index);
ListeDC_game* get_element_from_last_list(ListeDC_list *liste, int index);
int get_size_listlist(ListeDC_list* liste);

