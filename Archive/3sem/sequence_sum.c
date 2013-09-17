#include <stdio.h>
extern int sequence_sum(int start, int stop);
int main(void){
  int start, stop, rez;
  start = 7; stop = 22; rez = 0;
  rez = sequence_sum(start, stop);
  printf("%d\n", rez);
  return 0;
}
