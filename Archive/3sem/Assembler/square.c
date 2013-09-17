#include <stdio.h>

extern double square(double a);

int main(void){
    double a;
    scanf("%lf\n", &a);
    printf("%lf\n", square(a));
    return 0;
}

