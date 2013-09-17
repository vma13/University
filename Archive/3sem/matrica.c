#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(void) {
  int n, k;
  int i, j;

  // Считываем размерности матрицы
  printf("n -> "); scanf("%d", &n);
  printf("k -> "); scanf("%d", &k);

  // Выделяем память под матрицу
  int **a = (int **) malloc(n*sizeof(int *));
  if (a == NULL) {
    printf("Error (%s:%d): %s\n", __FILE__, __LINE__, strerror(errno)); exit(EXIT_FAILURE);
  }
  for (i = 0; i < n; i++) {
    a[i] = (int *) malloc(k*sizeof(int));
    if (a[i] == NULL) {
      printf("Error (%s:%d): %s\n", __FILE__, __LINE__, strerror(errno)); exit(EXIT_FAILURE);
    }
  }

  // Считываем матрицу
  for (i = 0; i < n; i++)
    for (j = 0; j < k; j++) {
      printf("a[%d][%d] -> ", i, j); scanf("%d", &a[i][j]);
    }

  // Печатаем матрицу
  for (i = 0; i < n; i++) {
    for (j = 0; j < k; j++)
      printf("%d ", a[i][j]);
    putchar('\n');
  }

  // Освобождаем память
  for (i = 0; i < n; i++)
    free(a[i]);
  	free(a);
  	
  return EXIT_SUCCESS;
}
