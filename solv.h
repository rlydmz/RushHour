
#ifndef H_SOLV
#define H_SOLV


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


bool is_move_allowed(cgame g, cpiece p, dir d);
bool touch_border(cgame g, cpiece p, dir d);
int nb_issues(cgame g);
void display(cgame g);
Fifo** clone_fifo(Fifo** farray, int nbClones);
game* get_issues(game g);

#endif // H_SOLV
