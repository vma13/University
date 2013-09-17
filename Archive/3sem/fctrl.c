#include <stdio.h>
int factorial(int x) { 
    if( x == 0 ) return 1;
    return x * factorial (x - 1);
}
void main() {
    int n;
    while( scanf("%d", &n) == 1)
      printf("%d\n", factorial (n));
}

