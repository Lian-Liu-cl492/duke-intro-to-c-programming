#include "future.h"
#include "input.h"
#include <stdio.h>


int main(void){
  FILE * f = fopen("test.txt", r);
  size_t * n = NULL;
  future_cards_t * fc;
  read_input(f, n, fc);
  return EXIT_SUCCESS;
}
