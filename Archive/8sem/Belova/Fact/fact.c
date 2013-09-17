#include <stdio.h>
main(){ 
  int n, i;
  double x = 1.0;
  printf("n = "); 
  scanf("%i", &n);
  for (i = 1; i <= n; i++) x *= i;  
  printf("Result: %.0lf\n", x);

  return 0; 
}
