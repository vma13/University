#include <stdio.h>
void foo(void){
  int n=0;
  printf("%d\n",n++);
}

int main(void){
  foo();
  foo();
  foo();
  return 0;
}
