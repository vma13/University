#include <stdio.h>

extern short vector_mult(short a, short b, short res);

int main(void){
    short a=4,b=3,res;
    //scanf("%lf%lf", &a, &num);
    printf("%hd\n", square(a,b,res));
    return 0;
}