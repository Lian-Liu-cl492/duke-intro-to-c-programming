#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  char *line = NULL;
  counts_t *c;

  FILE* f = fopen(filename, "r");
  if (f == NULL) {
    perror("cannot read file");
    exit(EXIT_FAILURE);
  }
  
  c = createCounts();
  size_t linesz = 0;
  ssize_t read;
  while ((read = getline(&line, &linesz, f)) >= 0) {
    if (read > 0 && line[read-1] == '\n'){
      line[read-1] = '\0';
    }
    addCount(c, lookupValue(kvPairs, line));
    free(line);
    line = NULL;
    linesz = 0;
  }
  free(line);
  fclose(f);
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {
    perror("Usage: ./count_values kv list\n");
    exit(EXIT_FAILURE);
  }

  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t* kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for(int i=2; i<argc; i++){
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t* c = countFile(argv[i], kv);

    //compute the output file name from argv[i] (call this outName)
    char* outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE* f = fopen(outName, "w");
    if (f == NULL) {
      perror("can't open file");
      exit(EXIT_FAILURE);
    }

    //print the counts from c into the FILE f
    printCounts(c, f);
    
    //close f
    fclose(f);

    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }

  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
