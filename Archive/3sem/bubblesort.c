#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(void){
int n;
  scanf("%d,&n");
  int *a=(int*)malloc(n*sizeof(int));
  int i;
  int j;
  for(i=0; i<n ; i++)
    for(j = n - 1;j < i ;j--)
      if(a[j-1] > a[j])
        n = a[j-1];
        a[j-1] = a[j];
        a[j] = n;
    bubble_sort(a,n);
  printf("%d ",a[i]);
  return 0;
  }
  
  
  
  
  
  
 /* void bubbleSort(T a[], long size) {
  long i, j;
  T x;

  for( i=0; i < size; i++) {            // i - номер прохода
    for( j = size-1; j > i; j-- ) {     // внутренний цикл прохода
      if ( a[j-1] > a[j] ) {
      x=a[j-1]; a[j-1]=a[j]; a[j]=x;
    }
  }
}
}*/