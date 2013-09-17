#include <stdio.h>
#include <malloc.h>

int max(int, int, int);
int max2(int, int, int, int);
void printArray(int **, int);
int **generate(int);

int main(void) {
  int size;
  printf("Enter size of matrix:");
  scanf("%d", &size);
  int **a = generate(size);
  int i, j, k;
  int **b = (int **)malloc(size*sizeof(int *));
  for( i = 0; i < size; i++)
    b[i] = (int *)malloc(size*sizeof(int));
  for( i = 0; i < size; i++)
    b[i][0] = a[i][0];
  for( j = 1; j < size; j++) {
    for( i = 0; i < size; i++) {
      for (k=1; k<size; k++){
      if( i == 0) b[i][j] = max( a[i][j], b[i+1][j-1], b[i][j-1] );
        else b[i][j] = max2( a[i][j], b[i-1][j-1], b[i+k][j-k], b[i-k][j+k] );
    }
  }
}
  printArray(b, size);
  free(a);
  free(b);
  return 0;
}

int **generate(int size) {
  int i, j;
  int **arr = (int **)malloc(size*sizeof(int *));
  for( i = 0; i < size; i++)
    arr[i] = (int *)malloc(size*sizeof(int));
  for( i = 0; i < size; i++) {
    printf("->");
    for( j = 0; j < size; j++)
      scanf("%d", &arr[i][j]);
  }
  return arr;
}

int max(int a, int b, int c) {
  return ( a > b && b > c )? a: ( b > a && b > c) ? b: c;
} 

int max2(int a, int b, int c, int d) {
  return ( a > b && a > c && a > d) ? a: ( b > a && b > c && b > d) ? b: ( c > b && c > a && c > d) ? c: d; 
}

void printArray(int **a, int size) {
  int i, j;
  for( i = 0; i < size; i++) {
    for( j = 0; j < size; j++)
      printf("%d ", a[i][j]);
    putchar('\n');
  }
}