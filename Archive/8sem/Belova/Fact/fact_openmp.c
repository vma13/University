#include <stdio.h>
#include <omp.h>
main(){ 
  int n, i;
  double t1, t2, x = 1.0;
  printf("n = "); 
  scanf("%i", &n);
  t1 = omp_get_wtime();
#pragma omp parallel for private(i) num_threads(2)
  for (i = 1; i <= n; i++) x *= i;
  t2 = omp_get_wtime();
  
  printf("Result: %.0lf\n", x);
  printf("Time: %lfs\n", (t2 - t1));
  return 0; 
}
