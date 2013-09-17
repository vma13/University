#include <stdio.h>
int main(void){
  int n,k;
  scanf("%d %d", &n, &k);
  fprintf(stdout,"stdout: n =%d\n",n);
  fprintf(stderr,"stderr: k =%d\n",k);
  return 0;
}