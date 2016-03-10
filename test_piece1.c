#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "piece.h"

#define NB_PIECES 4

/**
 * @brief test if value is equal to expected; if not, displays an error message containing msg to standard error output 
 * @return true if expected==value
 */
bool test_equality_int(int expected, int value, char * msg) {
  if (expected != value)
    fprintf(stderr,"ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
  return expected == value;
}

/**
 * @brief test if value is equal to expected; if not, displays an error message containing msg to standard error output 
 */
bool test_equality_bool(bool expected, bool value, char * msg) {
  if (expected != value)
    fprintf(stderr,"ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
  return expected == value;
}

piece pieces[NB_PIECES];
/* configue de test
.....3
.....3
...003
......
...122
...1..
 */
void set_up_pieces_rh() {
  pieces[0] = new_piece_rh(3, 3, true, true);
  pieces[1] = new_piece_rh(3, 0, true, false);
  pieces[2] = new_piece_rh(4, 1, true, true);
  pieces[3] = new_piece_rh(5, 3, false, false);
}

piece pieces_ane[NB_PIECES];
/* configue de test
..00..
..00..
......
..11..
..22..
.....3
 */
void set_up_pieces_ane(){
  pieces_ane[0] = new_piece(2,1,2,2,true,true);
  pieces_ane[1] = new_piece(2,3,2,1,true,true);
  pieces_ane[2] = new_piece(2,4,2,1,true,true);
  pieces_ane[3] = new_piece(5,5,1,1,true,true);
}

void tear_down_rh() {
  for (int i = 0 ; i < NB_PIECES; i++)
    delete_piece(pieces[i]);
}

void tear_down_ane() {
  for (int i = 0 ; i < NB_PIECES; i++)
    delete_piece(pieces_ane[i]);
}

bool test_new_piece_rh() {
  bool result = true;
  for (int x= 0 ; x < 5; x++)
    for (int y= 0 ; y < 5; y++)
      for (bool small=false; !small ; small= !small)
        for (bool horizontal=false; !horizontal ; horizontal= !horizontal) {
          int size;
          if (small)
            size = 2;
          else
            size = 3;
          piece p = new_piece_rh(x, y, small, horizontal);
          result = result && test_equality_int(x, get_x(p),"get_x");
          result = result && test_equality_int(y, get_y(p),"get_y");
          if (horizontal) {
            result = result && test_equality_int(1, get_height(p), "get_height");
            result = result && test_equality_int(size, get_width(p), "get_width");
          }
          else {
            result = result && test_equality_int(size, get_height(p), "get_height");
            result = result && test_equality_int(1, get_width(p), "get_width");
          }
          delete_piece(p);
        }
  return result;
}

bool test_new_piece_ane() {
  bool result = true;
  for (int x= 0 ; x < 5; x++)
    for (int y= 0 ; y < 5; y++)
      for(int width= 0; width < 5; width++)
	for(int height= 0; height < 5; height++)
	  for(bool movex=false; !movex; movex= !movex)
	    for(bool movey=false; !movey; movey= !movey){
	      piece p = new_piece(x, y, width, height, movex, movey);
	      result = result && test_equality_int(x, get_x(p), "get_x");
	      result = result && test_equality_int(y, get_y(p), "get_y");
	      result = result && test_equality_int(width, get_width(p), "get_width");
	      result = result && test_equality_int(height, get_height(p), "get_height");
	      result = result && test_equality_bool(movex, can_move_x(p), "can_move_x");
	      result = result && test_equality_bool(movey, can_move_y(p), "can_move_y");
	      delete_piece(p);
	    }
  return result;
}

bool test_intersect_rh() {
  bool result = true;
  set_up_pieces_rh();
  for (int i=0; i < NB_PIECES; ++i){
    for (int j =0; j<NB_PIECES; j++) {
      result = result && test_equality_bool(i==j, intersect(pieces[i], pieces[j]),"intersect");
    }
  }

  piece pb_piece1 = new_piece_rh(3, 3, false, false);
  piece pb_piece2 = new_piece_rh(3, 1, false, false);
  result = result && test_equality_bool(true, intersect(pieces[0], pb_piece1),"intersect pb1");
  result = result && test_equality_bool(true, intersect(pb_piece2, pb_piece1),"intersect pb2");
  delete_piece(pb_piece1);
  delete_piece(pb_piece2);
  tear_down_rh();
  return result;
}

bool test_intersect_ane() {
  bool result = true;
  set_up_pieces_ane();
  for (int i=0; i < NB_PIECES; ++i){
    for (int j =0; j<NB_PIECES; j++) {
      result = result && test_equality_bool(i==j, intersect(pieces_ane[i], pieces_ane[j]),"intersect");
      if(result == false)
	printf("Probleme avec les pieces %d et %d ! \n", i, j);
    }
  }

  piece pb_piece3 = new_piece(2, 1, 1, 1 ,true, true);
  piece pb_piece4 = new_piece(2, 1, 2, 1 ,true, true);
  result = result && test_equality_bool(true, intersect(pieces_ane[0], pb_piece3),"intersect pb3");
  result = result && test_equality_bool(true, intersect(pb_piece4, pb_piece3),"intersect pb4");
  delete_piece(pb_piece3);
  delete_piece(pb_piece4);
  tear_down_ane();
  return result;
}

bool test_move_rh() {
  bool result = true;
  piece p = new_piece_rh(0, 0, true, true);
  set_up_pieces_rh();
  for (int dist = 1; dist < NB_PIECES; dist++)
    for (int i=0; i < NB_PIECES; i++) {
      copy_piece(pieces[i],p);
      move_piece(p, LEFT, dist);
      if (is_horizontal(pieces[i]))
        result = result && test_equality_int(get_x(pieces[i])-dist,get_x(p),"move LEFT");
      else
        result = result && test_equality_int(get_x(pieces[i]),get_x(p),"move LEFT");
      copy_piece(pieces[i],p);
      move_piece(p, RIGHT, dist);
      if (is_horizontal(pieces[i]))
        result = result && test_equality_int(get_x(pieces[i])+dist,get_x(p),"move RIGHT");
      else
        result = result && test_equality_int(get_x(pieces[i]),get_x(p),"move RIGHT");
      copy_piece(pieces[i],p);
      move_piece(p, UP, dist);
      if (!is_horizontal(pieces[i]))
        result = result && test_equality_int(get_y(pieces[i])+dist,get_y(p),"move UP");
      else
        result = result && test_equality_int(get_y(pieces[i]),get_y(p),"move UP");
      copy_piece(pieces[i],p);
      move_piece(p, DOWN, dist);
      if (!is_horizontal(pieces[i]))
        result = result && test_equality_int(get_y(pieces[i])-dist,get_y(p),"move DOWN");
      else
        result = result && test_equality_int(get_y(pieces[i]),get_y(p),"move DOWN");


    }
  tear_down_rh();
  delete_piece(p);
  return result;
  return false;
}


bool test_move_ane() {
  bool result = true;
  piece p = new_piece_rh(0, 0, true, true);
  set_up_pieces_ane();
  for (int dist = 1; dist < NB_PIECES; dist++)
    for (int i=0; i < NB_PIECES; i++) {
      copy_piece(pieces_ane[i],p);
      move_piece(p, LEFT, dist);
      if (is_horizontal(pieces[i]))
        result = result && test_equality_int(get_x(pieces[i])-dist,get_x(p),"move LEFT");
      else
        result = result && test_equality_int(get_x(pieces[i]),get_x(p),"move LEFT");
      copy_piece(pieces[i],p);
      move_piece(p, RIGHT, dist);
      if (is_horizontal(pieces[i]))
        result = result && test_equality_int(get_x(pieces[i])+dist,get_x(p),"move RIGHT");
      else
        result = result && test_equality_int(get_x(pieces[i]),get_x(p),"move RIGHT");
      copy_piece(pieces[i],p);
      move_piece(p, UP, dist);
      if (!is_horizontal(pieces[i]))
        result = result && test_equality_int(get_y(pieces[i])+dist,get_y(p),"move UP");
      else
        result = result && test_equality_int(get_y(pieces[i]),get_y(p),"move UP");
      copy_piece(pieces[i],p);
      move_piece(p, DOWN, dist);
      if (!is_horizontal(pieces[i]))
        result = result && test_equality_int(get_y(pieces[i])-dist,get_y(p),"move DOWN");
      else
        result = result && test_equality_int(get_y(pieces[i]),get_y(p),"move DOWN");


    }
  tear_down_ane();
  delete_piece(p);
  return result;
  return false;
}


bool test_copy() {
  piece p = new_piece_rh(0, 0, true, true);
  bool result = true;
  set_up_pieces_rh();
  for (int i = 0 ; i < NB_PIECES; i++) {
    copy_piece(pieces[i],p);
    result = result && test_equality_int(get_height(pieces[i]), get_height(p), "copy get_height");
    result = result && test_equality_int(get_width(pieces[i]), get_width(p), "copy get_width");
    result = result && test_equality_int(get_x(pieces[i]), get_x(p), "copy get_x");
    result = result && test_equality_int(get_y(pieces[i]), get_y(p), "copy get_y");
    result = result && test_equality_bool(is_horizontal(pieces[i]), is_horizontal(p), "copy is_horizontal");
  }
  tear_down_rh();
  delete_piece(p);
  return result;
}

int main (int argc, char *argv[])
{
  bool result= true;

  /** Test des pieces_rh **/
  result = result && test_equality_bool(true, test_new_piece_rh(), "new_piece_rh");
  result = result && test_equality_bool(true, test_intersect_rh(), "intersect_rh");
  result = result && test_equality_bool(true, test_move_rh(), "move_rh");
  result = result && test_equality_bool(true, test_copy(), "copy");

  /**Test des pieces générames **/
  result = result && test_equality_bool(true, test_new_piece_ane(), "new_piece_ane");
  result = result && test_equality_bool(true, test_intersect_ane(), "intersect_ane");
  //result = result && test_equality_bool(true, test_move_ane(), "move_ane");
  
  if (result){
    printf("Youpi ! \n");
    return EXIT_SUCCESS;
  }
  else
    return EXIT_FAILURE;
}
