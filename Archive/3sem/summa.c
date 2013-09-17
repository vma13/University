#include <stdio.h>
const int n_max=10;
int main (void){
  double s=0;
  int i;
  for (i=1;i<=n_max;i++){
    s=s+1.0/i;
  }
  printf("%lf\n",s);
  return 0;
}
