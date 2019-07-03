#include <stdlib.h>
#include <stdio.h>

typedef struct _retire_info{
  int months;
  double contribution, rate_of_return;
}retire_info;

double balance_cal(int startAge, double initial, retire_info info){
  printf("Age %3d month %2d you have $%.2f\n", startAge/12, startAge%12, initial);
  initial = initial * (1+info.rate_of_return) + info.contribution;
  return initial;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired){
  for(int i=1; i<= working.months; i++){
    initial = balance_cal(startAge, initial, working);
    startAge++;
  }
  for(int i=1; i<= retired.months; i++){
    initial = balance_cal(startAge, initial, retired);
    startAge++;
  }
}

int main(void){
  retire_info working = {.months=489, .contribution=1000, .rate_of_return=0.045/12};
  retire_info retired = {.months=384, .contribution=-4000, .rate_of_return=0.01/12};
  retirement(327, 21345.0, working, retired);
  return 0;
}
