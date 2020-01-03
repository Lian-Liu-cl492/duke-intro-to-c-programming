#include "input.h"
#include <string.h>

deck_t * hand_from_string(const char * str, future_cards_t * fc){
  deck_t * hand = malloc(sizeof(*hand));
  hand->cards = NULL;
  hand->n_cards = 0;
  char delim[] = " ";
  char * p = strdup(str);
  if (strlen(p) > 0){
    p[strlen(p) - 1] = '\0';
  }
  char *ptr = strtok(p, delim);
  while(ptr != NULL)
  {
    if(ptr[0] == '?'){
      add_empty_card(hand);
      char * s = strndup(ptr+1, strlen(ptr)-1);
      add_future_card(fc, atoi(s), hand->cards[hand->n_cards - 1]);
      free(s);
    } else {
      card_t c = card_from_letters(ptr[0], ptr[1]);
      add_card_to(hand, c);
    }
    ptr = strtok(NULL, delim);
  }
  free(p);

/*
  const char * p1 = str;
  const char * p2 = strchr(str, ' ');
  while(p1 != '\0'){
    fprintf(stderr, "p1 = %s\n", p1);
    if(*p1 == '?'){
      add_empty_card(hand);
      char * s = strndup(p1+1, p2-p1-1);
      fprintf(stderr, "s = %s\n", s);
      add_future_card(fc, atoi(s), hand->cards[hand->n_cards - 1]);
      free(s);
    } else {
      card_t c = card_from_letters(*p1, *(p1+1));
      add_card_to(hand, c);
    }
    p1 = p2+1;
    p2 = strchr(p2+1, ' ');
    if(p2 == NULL){
      p2 = strchr(p1, '\n');
    }
  }
*/
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
