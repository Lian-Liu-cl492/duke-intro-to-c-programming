#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void count_char(FILE * f, int* freq_count) {    
  int c;
  while ((c = fgetc(f)) != EOF) {        
    if (isalpha(c)) {            
      c = tolower(c);            
      c -= 'a';            
      freq_count[c]++;
    }        
  }
}

int most_freq(int* freq_count){
  int e_index = 0;
  for(int i=0; i<26; i++){
    if(e_index<freq_count[i])
      e_index = i;
  }
  int key = e_index + ((e_index >=7) ? -7 : 19);
  return key;
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
  int freq_count[26] = {0};
  count_char(f, freq_count);
  int key = most_freq(freq_count); 
  if (fclose(f) != 0) {    
    perror("Failed to close the input file!");    
    return EXIT_FAILURE;  
  }  
  printf("%d",  key);
}
