#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void){
/*	char *str1 = "Hello!";
	char *str2=(char *)malloc(30);
	int i,j;
	str2[0]='1'; str2[1]='2'; str2[2]='\0';
	for(i=0; str1[i]!=0; i++){
		printf("str1[%d] = %c = %d\n", i, str1[i], str2[i]);
	}
	
	unsigned strlen(const char *str){
		unsigned j;
		
		for(j=0;str[j]!=0;j++){
			return j;
		}
	}

				
	printf("%d\n", strlen(str2));
	printf("%d\n", j);
	printf("%s\n", str2);
	strcat(str2, str1);
*/
/*	int *a=(int *)malloc(5*sizeof(int));
	int i;
	for(i=0;i<5;i++){
		printf("a[%d]-> ",i);scanf("%d", &a[i]);	
	}
	
	for(i=0;i<5;i++)
		printf("&a[%d]=%p;""a[%d]=%d\n",i,&a[i],i,a[i]);
		
	int *ai;
	for(ai=a,i=0; i<5; ai++, i++)
		printf("ai=%p; i=%d\n", ai, i);
*/
	struct{
		int x,y;
	} var;
}
