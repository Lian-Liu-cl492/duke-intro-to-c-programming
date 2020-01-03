#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

int main(int argc, char ** argv) {
  //YOUR CODE GOES HERE
  int n_trials;
  if(argc == 3){
    n_trials = atoi(argv[2]);
  } else if(argc == 2){
    n_trials = 10000;
  } else{ 
    return EXIT_FAILURE;
  }
  char * filename = argv[1];
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("cannot read file");
    exit(EXIT_FAILURE);
  }

  size_t n = 0;
  size_t * n_hands = &n;
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->decks = malloc(sizeof(*(fc->decks)));
  fc->n_decks = 0;
  
  deck_t ** hands = read_input(f, n_hands, fc);
  deck_t * deck = build_remaining_deck(hands, *n_hands);
  int * n_wins = malloc(sizeof(*n_wins) * (*(n_hands)+1));
  for(size_t i=0; i<*(n_hands)+1 ; i++){
    n_wins[i] = 0;
  }
  
  for(size_t j=0; j<n_trials ; j++){
    shuffle(deck);
    future_cards_from_deck(deck, fc);
    int winner_idx = 0;
    int tie = 0;
    for(size_t i=1; i<*n_hands ; i++){  // Start from one to avoid tie with itself
      if(compare_hands(hands[winner_idx], hands[i]) == -1){
        winner_idx = i;
        tie = 0;
      } else if (compare_hands(hands[winner_idx], hands[i]) == 0){
        tie = 1;
      }
    }
    if(tie){
      n_wins[*n_hands]++;
    } else{
      n_wins[winner_idx]++;
    }
  }

  for(size_t i=0; i<*n_hands ; i++){
    printf("Hand %zu won %u / %u times (%.2f%%)\n", i, n_wins[i], n_trials, 100*n_wins[i]/(double)n_trials);
  }
  printf("And there were %u ties\n", n_wins[*n_hands]);
  
    
  free(n_wins);
  free(fc->decks);
  free(fc);
  fclose(f);
  return EXIT_SUCCESS;
}
