#include <txx>
#include <stdio.h>
#include <stdlib.h>

tfun double fact (int n) {
  return n < 1 ? 1 : n * fact(n - 1);
}

tfun int main (int argc, char *argv[]) {
  if (argc != 2) { printf("Usage: fib <n>\n"); return 1; }
  int n = atoi(argv[1]);
  
  printf("fact(%d) = %.0lf\n", n, (double)fact(n));
  return 0;
}
