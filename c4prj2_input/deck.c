#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  for(int i=0; i<hand->n_cards; i++){
    print_card( **((hand->cards)+i) );
    if(i != hand->n_cards){
      printf(" ");
    } 
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

void add_card_to(deck_t * deck, card_t c){
  deck->cards = realloc(deck->cards, sizeof(*(deck->cards)) * (++deck->n_cards));
  deck->cards[deck->n_cards - 1] = malloc(sizeof(*(deck->cards[deck->n_cards - 1])));
  deck->cards[deck->n_cards - 1]->value = c.value;
  deck->cards[deck->n_cards - 1]->suit = c.suit;
}

card_t * add_empty_card(deck_t * deck){
  deck->cards = realloc(deck->cards, sizeof(*(deck->cards)) * (++deck->n_cards));
  deck->cards[deck->n_cards - 1] = malloc(sizeof(*(deck->cards[deck->n_cards - 1])));
  deck->cards[deck->n_cards - 1]->value = 0;
  deck->cards[deck->n_cards - 1]->suit = 0;
  return deck->cards[deck->n_cards - 1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards){
  deck_t * deck = malloc(sizeof(*deck));
  deck->n_cards = 0;
  deck->cards = malloc(sizeof(*(deck->cards)));
  for(int i=0; i<52; i++){
    card_t c = card_from_num(i);
    if(!deck_contains(excluded_cards, c)){
      add_card_to(deck, c);
    }
  }
  return deck;
}

void free_deck(deck_t * deck){
  for(int i=0; i< deck->n_cards; i++){
    free(deck->cards[i]);
  }
  free(deck->cards);
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands){
  deck_t * excluded_cards = malloc(sizeof(*excluded_cards));
  excluded_cards->n_cards = 0;
  excluded_cards->cards = malloc(sizeof(*(excluded_cards->cards)));
  for(int i=0; i<n_hands; i++){
    for(int j=0; j<hands[i]->n_cards; j++){
      if(suit_letter(*hands[i]->cards[j]) != 'x'){
        add_card_to(excluded_cards, *(hands[i]->cards[j]));
      }
    }
  }
  deck_t * deck = make_deck_exclude(excluded_cards);
  free_deck(excluded_cards);
  return deck;
}

