#include <stdio.h>

const float nmax=10;

int main(void){
 float n=1.0;
 float sum=0.0;
  while(n<=nmax){
   sum=sum+(1/n);
   n++;
  }
printf("%f\n", sum);
return 0;
}
