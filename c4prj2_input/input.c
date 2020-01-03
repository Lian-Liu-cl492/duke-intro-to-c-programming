#include "input.h"

deck_t * hand_from_string(const char * str, future_cards_t * fc){
  deck_t * hand = malloc(sizeof(*hand));
  hand->cards = NULL;
  hand->n_cards = 0;
  while(*str != '\n' && *(str+1) != '\n' && *(str+2) != '\n'){
    if(*str == '?'){
      add_empty_card(hand);
      add_future_card(fc, atoi(*(str+1)), hand->cards[hand->n_cards - 1])
    } else {
      card_t c = card_from_letters(*str, *(str+1));
      add_card_to(hand, c);
    }
    str += 3;
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
    hands[*n_hands - 1] = hand;
    free(line);
    linesz = 0;
  }
  free(line);
  return hands;
}
