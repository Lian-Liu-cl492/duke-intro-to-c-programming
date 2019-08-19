#include <stdio.h>
#include <stdlib.h>


int main(){
  FILE* f = fopen("char255.txt", "r");
  if (f == NULL) { /* error handling code omitted */; }
  char c;
  while ((c = fgetc(f)) != EOF) {
    printf("%d",c);
    break;
  }
}


