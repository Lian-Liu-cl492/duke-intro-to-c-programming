#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n){
  if(n == 0 || n == 1){
    return n;
  }
  size_t max_len = 0;
  size_t current_len = 0;
  for(int i=1; i<n; i++){
    if(array[i] > array[i-1])
      current_len++;
    else
      current_len = 0;
    if(current_len > max_len)
      max_len = current_len;
  }
  return max_len;
}

