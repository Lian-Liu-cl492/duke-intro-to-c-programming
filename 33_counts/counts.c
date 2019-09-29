#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

counts_t * createCounts(void) {
  counts_t * counts = malloc(sizeof(*counts));
  counts->array = malloc(sizeof(*counts->array));
  counts->size = 1;
  counts->array[0] = malloc(sizeof(*(counts->array[0])));
  counts->array[0]->name = "unknown";
  counts->array[0]->num = 0;
  return counts;
}

void addCount(counts_t * c, const char * name) {
  if(name == NULL){
    ++(c->array[0]->num);
    return;
  }
  for(int i=1; i<c->size; ++i){
    if(strcmp(name, c->array[i]->name) == 0){
      ++(c->array[i]->num);
      return;
    }
  }
  c->array = realloc(c->array, sizeof(*(c->array)) * (++c->size));
  c->array[c->size -1] = malloc(sizeof(*(c->array[c->size-1])));
  c->array[c->size -1]->name = malloc((strlen(name)+1) * sizeof(char*));
  strcpy(c->array[c->size -1]->name, name);
  c->array[c->size -1]->num = 1;
}

void printCounts(counts_t * c, FILE * outFile) {
  for(int i=1; i<c->size; i++){
    fprintf(outFile, "%s: %zu\n", c->array[i]->name, c->array[i]->num);
  }
  if(c->array[0]->num >0){
    fprintf(outFile, "<unknown>: %zu\n", c->array[0]->num);
  }
}

void freeCounts(counts_t * c) {
  free(c->array[0]);
  for(int i=1; i<c->size; i++){
   free(c->array[i]->name);
   free(c->array[i]);
  }
  free(c->array);
  free(c);
}
