#include "input.h"

deck_t * hand_from_string(const char * str, future_cards_t * fc){
  deck_t * hand = malloc(sizeof(*hand));
  hand->cards = NULL;
  hand->n_cards = 0;
  char * curr = str;
  while(*curr != '\n'){
    hand->cards = realloc(hand->cards, sizeof(*(hand->cards)) * ++hand->n_cards);
    hand->cards[hand->n_cards - 1] = card_from_letters(*curr, *(curr+1));
    curr += 3;
  }
  if(hand->n_cards < 5){
    perror("Number of cards is less than five!");
    exit(EXIT_FAILURE);
  }
  return hand;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc){
  deck_t ** hands = malloc(sizeof(*hands));
  *n_hands = 0;
  
  char * line = NULL;
  size_t linesz = 0;
  while (getline(&line, &linesz, f) >= 0) {
    deck_t * hand = hand_from_string(line, fc);
    hands = realloc(hands, sizeof(*hands) * ++(*n_hands));
    hands[n_hands - 1] = hand;
    free(line);
    linesz = 0;
  }
  free(line);
  return hands;
}
