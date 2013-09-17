#include <stdio.h>
extern  short array_to_digit(short* array, int size);
int main (void){
  short a[4]={1,2,3,5};
  int size = 4;
  printf("%d",array_to_digit(a,size));
  return 0;
}

