#include <stdio.h>
extern double square(double a);
int main(void){
  double a = 2;
  double s = square(a);
  printf("%d\n", s);
return 0;
}
