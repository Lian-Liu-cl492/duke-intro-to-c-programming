#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  for(int i=0; i<hand->n_cards; i++){
    print_card( **((hand->cards)+i) );
  }
}

int deck_contains(deck_t * d, card_t c) {
  for(int i=0; i<d->n_cards; i++){
    if( (*(d->cards+i))->value == c.value && (*(d->cards+i))->suit== c.suit)
    return 1;
  }
  return 0;
}

void shuffle(deck_t * d){
  card_t * temp;
  for(int i=0; i<d->n_cards; i++){
    int rand_num = random()%d->n_cards;
    while( rand_num== i)
      rand_num = random()%d->n_cards;

    temp = *((d->cards)+i);
    *((d->cards)+i) = *((d->cards)+rand_num);
    *((d->cards)+rand_num) = temp;
  }
}

void assert_full_deck(deck_t * d) {
  for(unsigned i=0; i<52; i++){
    assert(deck_contains(d, card_from_num(i)));
  }
}
