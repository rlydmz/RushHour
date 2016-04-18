
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"

typedef struct ListElem ListElem;
struct ListElem{
    game g;
    ListElem *next;
    ListElem *prev;
};

typedef struct ListeDC ListeDC;
struct ListeDC{
    ListElem *first;
    ListElem *last;
};

ListeDC *init_list();
void insert_first(ListeDC *liste, game g);
void insert_last(ListeDC *liste, game g);
void delete_first(ListeDC *liste);
void delete_last(ListeDC *liste);
game get_first(ListeDC *liste);
game get_last(ListeDC *liste);
game get_element_from_first(ListeDC *liste, int index);
game get_element_from_last(ListeDC *liste, int index);
int get_size(ListeDC* liste);
