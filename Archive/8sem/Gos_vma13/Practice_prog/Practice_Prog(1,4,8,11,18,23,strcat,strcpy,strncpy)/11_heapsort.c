#include <stdio.h>
#include <malloc.h>

void print_array(int*, unsigned int);
void downHeap(int*, long, long);
void heapSort(int*, long);

int main(int argc, char **argv) {
  long size, i;
  int *array;
  printf("Enter size of array: ");
  scanf("%u", &size);
  array = (int*)malloc(size*sizeof(int));
  for( i = 0; i < size; i++)
    scanf("%d", &array[i]);
  printf("Before sort--> ");
  print_array(array, size);
  heapSort(array, size);
  printf("After sort--> ");
  print_array(array, size);
  while(1);
  return 0;
}

void print_array(int *arr, unsigned int size) {
  unsigned int i;
  for(i = 0; i < size; i++)
    printf("%d  ", arr[i]);
  putchar('\n');
}

void downHeap(int *a, long k, long n) {
  //  ��������� ����������� ���������� �������� 
  //  �� ���������: a[k+1]...a[n]  - �������� 
  //  �����:  a[k]...a[n]  - �������� 
  int new_elem;
  unsigned long child;
  new_elem = a[k];
  while(k <= (n/2)) { // ���� � a[k] ���� ���� 
    child = 2*k;
    //  �������� �������� ���� 
    if( child < n && a[child] < a[child+1] ) 
      child++;
    if( new_elem >= a[child] ) break; 
    // ����� 
    a[k] = a[child]; 	// ��������� ���� ������ 
    k = child;
  }
  a[k] = new_elem;
}

void heapSort(int *a, long size) {
  long i;
  int temp;
  // ������ �������� 
  for( i = (size/2 - 1); i >= 0; i--) 
    downHeap(a, i, size-1);
  // ������ a[0]...a[size-1] �������� 
  for( i = size-1; i > 0; i--) {
    // ������ ������ � ��������� 
    temp = a[i]; 
    a[i] = a[0]; 
    a[0]=temp;
    // ��������������� ��������������� a[0]...a[i-1] 
    downHeap(a, 0, i-1); 
  }
}
