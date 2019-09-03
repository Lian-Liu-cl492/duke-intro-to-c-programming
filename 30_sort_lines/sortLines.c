#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void readResult(FILE * f){
  char ** lines = NULL;
  size_t num_lines = 0;
  char * line = NULL;
  size_t sz =0;
  while(getline(&line, &sz, f)){
    num_lines++;
    lines = realloc(lines, sizeof(*lines) * num_lines);
    lines[num_lines - 1] = line;
    line = NULL;
  }
  free(line);

  sortData(lines, num_lines);

  for(int i=0; i<num_lines; i++){
    printf("%s", lines[i]);
    free(lines[i]);
  }
  free(lines);
}

int readFiles(char ** file_list, size_t len){
  for(int i = 0; i<len; i++){
    FILE* f = fopen(file_list[i], "r");
    if(f == NULL){
      fprintf(stderr, "Cannot open %s", file_list[i]);
      return EXIT_FAILURE;
    }
    readResult(f);
    fclose(f);
  }
  return EXIT_SUCCESS;
}

int main(int argc, char ** argv) {
  
  //WRITE YOUR CODE HERE!
  if(argc == 1){
    readResult(stdin);
  }
  else{
    return readFiles(argv+1, argc-1);
  }  
  return EXIT_SUCCESS;
}
