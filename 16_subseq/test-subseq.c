#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(void){
  int array1[] = {-1, 0};
  if(maxSeq(array1, 2) !=2){
    return EXIT_FAILURE;
  }
  int array2[] = {1, 1};
  if(maxSeq(array2, 2) !=1){
    return EXIT_FAILURE;
  }
  int array3[] = {1};
  if(maxSeq(array3, 1) !=1){
    return EXIT_FAILURE;
  }
  if(maxSeq(NULL, 0) !=0){
    return EXIT_FAILURE;
  }
  int array4[] = {1, 2, 5, 4, 6};
  if(maxSeq(array4, 5) !=3){
    return EXIT_FAILURE;
  }
  int array5[] = {1, 2, 3, 1, 2, 4, 1, 2, 3};
  if(maxSeq(array5, 9) !=3){
    return EXIT_FAILURE;
  }
  int array6[] = {1,2,7,3,8,12,16};
  if(maxSeq(array6, 7) !=4){
    return EXIT_FAILURE;
  }
  printf("Pass all test cases!");
  return EXIT_SUCCESS;
}
