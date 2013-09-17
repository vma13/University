#include <stdio.h>
#include "arithmetic.h"

int main(void) {
  int a = 2, b = 3;
  printf("%d\n", sum(a,mul(b,7)));
  return 0;
}
