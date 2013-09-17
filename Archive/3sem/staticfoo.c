#include <stdio.h>
static int n = 0;
void foo(void){
  static int k = 0;
  n++;k++;
  printf("n=%d, k=%d\n",n,k);
}
void bar(void){
  static int m=0;
  n--;m--;
  printf("n=%d, m=%d\n",n,m);
}
int main(void){
  foo();foo();foo();bar();bar();
  return 0;
}