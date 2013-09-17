#include <stdio.h>
#include <stdlib.h>

/*	//int *a=(int *)malloc(sizeof(int));
	int a=3;
	// printf("*a=%d\n",*a);
	printf("a=%p\n", &a);
	return 0;
	
*/
//массивы:
//	int arr[]={1,2,3}; //куча
/*строка
	char arr[]="abc";
*/	
/*	int *a=(int *)malloc(3*sizeof(int));
	a[0]=1;
	a[1]=2;
	a[2]=3;
	int i;
	for(i=0; i<3; i++)
		printf("%d ", a[i]);
		free(a);
		return 0;
*/
//2mern_matrica
int main(void){
	int	n,k;
	int **a;
	int i,j;
	printf("n= "); scanf("%d", &n);
	printf("k= "); scanf("%d", &k);
	a=(int **)malloc(n*sizeof(int *));
	for(i=0; i<n; i++)
		a[i]=(int *)malloc(k*sizeof(int));
	for(i=0; i<n; i++)
		for(j=0; j<k; j++){
			printf("a[%d][%d]= ",i,j);
			scanf("%d",&a[i][j]);
		}
	for(i=0; i<n; i++)
		for(j=0; j<k; j++){
			printf("%d ", a[i][j]);
//			printf("\n");
		}
	return 0;
}
