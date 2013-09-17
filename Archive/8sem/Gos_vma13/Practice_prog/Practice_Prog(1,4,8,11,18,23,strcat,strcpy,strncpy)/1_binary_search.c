#include <stdio.h>
#include <malloc.h>

unsigned int BinarySearch(int*, unsigned int, int);

int main( void ){
  unsigned int size, i;
  int *array, n;
  while( 1 ) {
    printf("Enter size of array: ");
    scanf("%u\n", &size);
    array = (int*)malloc(size*sizeof(int));
    for(i = 0; i < size; i++) 
      scanf("%d", &array[i]);
    printf("Enter element for search: ");
    scanf("%d", &n);
    printf("%u\n", BinarySearch(array, size, n));
  }
}

unsigned int BinarySearch(int* array, unsigned int size, int searchKey) {
 unsigned int middle, low, high;
 low = 0;
 high = size;
 while(low <= high) {
   middle = (low + high) >> 1;
   if(searchKey == array[middle])
     return middle;
   else if(searchKey < array[middle])
     high = middle - 1;
   else
     low = middle + 1;
 }
 return low >= size ? size-1 : low;
}
