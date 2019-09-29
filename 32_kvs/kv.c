#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"


kvpair_t * splitPair(char * data){
  char * p = strchr(data, '=');
  if(p == NULL){
    return NULL;
  }
  *p ='\0';
  char * newline = strchr(p+1, '\n');
  if(newline != NULL){
    *newline = '\0';
  }

  kvpair_t * res = malloc(sizeof(*res));
  res->key = malloc((strlen(data)+1) * sizeof(char*));
  res->value = malloc((strlen(p+1)) * sizeof(char*));
  strcpy(res->key, data);
  strcpy(res->value, p+1);
  return res;
}

void addKVPair(kvarray_t * kvarray, kvpair_t * pair){
  for(int i=0; i<kvarray->size; ++i){
    if(kvarray->array[i]->key == pair->key){
      kvarray->array[i]->value = pair->value;
      return;
    }
  }

  kvarray->array = realloc(kvarray->array, (++kvarray->size) * sizeof(*(kvarray->array)));
  kvarray->array[kvarray->size -1] = pair;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if(f == NULL){
    return NULL;
  }
  kvarray_t* result = malloc(sizeof(*result));
  result->array = malloc(0);//sizeof(*result->array));
  result->size = 0;
  char* line = NULL;
  size_t sz = 0;
  while(getline(&line, &sz, f) >= 0){
    kvpair_t * pair = splitPair(line);
    if (pair == NULL){
      return NULL;
    }
    addKVPair(result, pair);
    free(line);
    line = NULL;
    sz = 0;
  }
  free(line);
  fclose(f);
  return result;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for(int i=0; i< pairs->size; ++i){
    free(pairs->array[i]->key);
    free(pairs->array[i]->value);
    free(pairs->array[i]);
  }
  free(pairs->array);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for(int i=0; i<pairs->size; ++i){
    printf("key = '%s' value = '%s'\n", pairs->array[i]->key, pairs->array[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for(int i=0; i<pairs->size; ++i){
    if(strcmp(pairs->array[i]->key, key) == 0){
      return pairs->array[i]->value;
    }
  }
  return NULL;
}
