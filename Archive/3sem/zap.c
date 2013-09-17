#include <stdio.h>
extern int progressia(int,int,int);
int main(void){
  int a=1;
  int n=2;
  int d=3;
  int s = progressia(a,n,d);
  printf("%d\n",s);
  return 0;
}