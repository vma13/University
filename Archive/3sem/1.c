#include <stdio.h>

int main(void){
	int x=2;
	{
		int y=3;
		printf("%d\n %d\n",x,y);
	}
	printf("%d\n",y);
	return 0;
}
