#include <stdio.h>
#include <stdlib.h>


int main(){
  char c =255;
  printf("%c", c);
  for(int i=0; i<9; i++)
    printf("c");
  for(int i=0; i<9; i++){
    printf("\n");
    for(int j=0; j<10; j++)
      printf("c");
  }
}
