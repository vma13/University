#include <stdio.h>
#include <malloc.h>

void print_array(int*, unsigned int);
void buble_sort(int*, unsigned int);
void insertion_sort(int*, unsigned int);
void selection_sort(int*, unsigned int);

int main(int argc, char **argv) {
  unsigned int i, size;
  int *array;
  printf("Enter size of array: ");
  scanf("%u", &size);
  array = (int*)malloc(size*sizeof(int));
  for( i = 0; i < size; i++)
    scanf("%d", &array[i]);
  printf("Before sort--> ");
  print_array(array, size);
  insertion_sort(array, size);
  printf("After sort--> ");
  print_array(array, size);
  return 0;
}

void print_array(int *arr, unsigned int size) {
  unsigned int i;
  for(i = 0; i < size; i++)
    printf("%d  ", arr[i]);
  putchar('\n');
}

/*
Сложность алгоритма: O(n^2)
Наихудший случай:
  Число обменов - (N-1)*N/2
  Суммарное число сравнений - (N-1)*N
Наилучший случай:
  Суммарное число сравнений - 2*(N-1)
  Число обменов - 0
*/
void buble_sort(int *arr, unsigned int size) {
  unsigned int i, j;
  int tmp;
  for( i = 0; i < size-1; i++) 
    for( j = i; j < size; j++) 
      if( arr[i] > arr[j] ) {           
        tmp = arr[j];
        arr[j] = arr[i];
        arr[i] = tmp; 
      }
}

void insertion_sort(int *arr, unsigned int size) {
  unsigned int i, j;
  int tmp;
  for ( i = 1; i < size; i++) {  
    tmp = arr[i];
    for ( j = i - 1; j >= 0 && arr[j] < tmp; j--)
      arr[j+1] = arr[j]; 
    arr[j+1] = tmp;
  }
}

/*
Сложность алгоритма: O(n^2)
Наихудший случай:
  Суммарное число сравнений N^2-1
  Число обменов N-1
Наилучший случай:
*/
void selection_sort(int *arr, unsigned int size) {
  unsigned int i, j, k;
  int tmp; 
  for( i = 0; i < size; i++) {   	
    k = i;
    tmp = arr[i];
    for( j = i + 1; j < size; j++)
      if( arr[j] < tmp ) {
        k  = j;
        tmp = arr[j];
      }
    arr[k] = arr[i];
    arr[i] = tmp;   	
  }
}
