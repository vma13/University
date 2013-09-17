#include <stdio.h>

extern short* vector_mult(const short* a, const short* b, short* res);

int main(void)
{
    const short a[3] = {9,1,5};    
    const short b[3] = {1,3,8};    
    short res[3] = {0,0,0};
    short* result = vector_mult(a,b,res);

    printf("a=[9,1,5]; b=[1,3,8]; res=[0,0,0]\n%d %d %d\n", result[0],
			 result[1],
			 result[2]);
    return 0;
}
