#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void check(unsigned x, unsigned y, unsigned expected_ans){
  if (power(x, y)!= expected_ans){
    printf("%d^%d != %d", x, y, expected_ans);
    exit(EXIT_FAILURE);
  }
}

int main(void){
  check(0, 0, 1);
  check(2, 2, 4);
  check(20, 0, 1);
  check(2, 1, 2);
  check(2, 3, 8);
  check(10000, 2, 100000000);
  return EXIT_SUCCESS;
}

	
