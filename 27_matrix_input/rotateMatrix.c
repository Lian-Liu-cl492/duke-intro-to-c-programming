#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate(char matrix[10][10]){
  char temp1;
  char temp2;
  for(int i=0; i<5; i++){
    for(int j=0; j<5; j++){
      temp1 = matrix[j][9-i];
      matrix[j][9-i] = matrix[i][j];
      temp2 = matrix[9-i][9-j];
      matrix[9-i][9-j] = temp1;
      temp1 = matrix[9-j][i];
      matrix[9-j][i] = temp2;
      matrix[i][j] = temp1;
    }
  }
}

int main(int argc, char ** argv) {  
  if (argc != 2) {    
    fprintf(stderr,"Usage: encrypt key inputFileName\n");    
    return EXIT_FAILURE;  
  }  
  
  FILE * f = fopen(argv[1], "r");  
  if (f == NULL) {    
    perror("Could not open file");    
    return EXIT_FAILURE;  
  }

  char matrix[10][10];
  int c;
  for(int i=0; i<10; i++){
    for(int j=0; j<10; j++){
      c = fgetc(f);
      if(c == '\n'){
        perror("Line is too short!");    
        return EXIT_FAILURE;  
      }
      if(c == EOF){
        perror("Too less lines!");    
        return EXIT_FAILURE;  
      }
      matrix[i][j] = c;
    }
    if((c = fgetc(f)) != '\n'){
      perror("Line is too long!");    
      return EXIT_FAILURE;  
    }
  }
  
  if((c = fgetc(f)) != EOF){
    perror("Too many lines!");    
    return EXIT_FAILURE;  
  }  
  rotate(matrix);  

  if (fclose(f) != 0) {    
    perror("Failed to close the input file!");    
    return EXIT_FAILURE;  
  }

  for(int i=0; i<10; i++){
    for(int j=0; j<10; j++){
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
  return EXIT_SUCCESS;
}
