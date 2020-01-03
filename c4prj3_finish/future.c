#include "future.h"
#include <stdio.h>

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr){
  if(index >= fc->n_decks){
    fc->decks = realloc(fc->decks, sizeof(*(fc->decks)) * (index + 1));
    for(size_t i = fc->n_decks; i<=index; i++){
      deck_t d = {.cards = NULL, .n_cards = 0};
      fc->decks[i] = d;
    }
    fc->n_decks = index+1;
  }
  deck_t * deck = &(fc->decks[index]);
  deck->cards = realloc(deck->cards, sizeof(*(deck->cards)) * (++deck->n_cards));
  deck->cards[deck->n_cards - 1] = malloc(sizeof(*(deck->cards[deck->n_cards - 1])));
  deck->cards[deck->n_cards - 1] = ptr;
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc){
  if(deck->n_cards < fc->n_decks){
    perror("The deck does not have enough cards!");
    exit(EXIT_FAILURE);
  }
  for(int i=0; i<fc->n_decks; i++){
    for(int j=0; j<fc->decks[i].n_cards; j++){
      fc->decks[i].cards[j]->value = deck->cards[i]->value;
      fc->decks[i].cards[j]->suit = deck->cards[i]->suit;
    }
  }
}
