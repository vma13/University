#include <stdio.h>
#include <stdlib.h>

int main(void){
	int *a;
	a=(int *) malloc (sizeof(int));
	printf("&a=%p; *a=%d\n", a, *a);
	*a=10;
	printf("&a=%p; *a=%d\n", a, *a);
	return 0;
}

	