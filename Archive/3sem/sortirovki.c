#include <stdio.h>
#include <string.h>
void sort (int size) {
	int a[size];
	int b[size];
	int t[size];
	int i = 0;
	int j = 0;
	int c, min, d;
	// input
	for (; i < size; i++) {
		scanf("%d", &a[i]);
		b[i] = a[i];
		a[i] = t[i];
	}
	// insertion sort for a
	for (i = 1; i < size; i++) {
		c = a[i];
		for (j = i - 1; j >= 0 && c < a[j]; j--)
			a[j+1] = a[j];
		a[j+1] = c;
	}
	// selection sort for b
	for (i = 0; i < size; i++) {
		min = i;
    //c = b[i];
		for (j = i + 1; j < size; j++)
			(b[j] < b[min]) ? (min = j) : (0);
    c = b[i];
    b[i] = b[min];
    b[min] = c;
	}
	// bubble sort for c
	for (i = 0; i < size; i++) {
    for (j < size - 1; j > i; j--) {
      if(t[j-1] > t[j]){
          d = t[j-1];
          t[j-1] = t[j];
          t[j] = d;
                
			}
    }
	}

	// output
	for (i = 0; i < size; i++)
		printf("%d  %d  %d\n", a[i], b[i], t[i]);
}


int main () {
	int size;
	scanf("%d", &size);
	sort(size);
}