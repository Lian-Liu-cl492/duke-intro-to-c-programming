#include "future.h"
#include "input.h"
#include <stdio.h>


int main(void){
  FILE * f = fopen("test.txt", "r");
  size_t num = 0;
  size_t * n = &num;
  future_cards_t * fc = malloc(sizeof(*fc));
  deck_t ** d = read_input(f, n, fc);
  printf("%zu\n", *n);
  for(size_t i=0; i<*n; i++){
    print_hand(d[i]);
  }
  free(fc);
  fclose(f);
  return EXIT_SUCCESS;
}
