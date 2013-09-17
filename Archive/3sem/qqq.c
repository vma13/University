#include <stdio.h>
int main(void){
  int i;
  int a;
  scanf("%d", &a);
  int f = 1;
  while(a<=1){
    printf("%d",a);
  }
  while(i>a&&i<1){
    i=i*f;
  }
  printf("%d",i);
}

