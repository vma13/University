#include <stdio.h>
int i, j;
for (i = 1; i < size; i++) {
	temp = array[i];
	for (j = i - 1; j >= 0; j--) {
		if (array[j] < temp) {
			break;
		}
		array[j+1] = array[j];
	}
	array[j+1] = temp;
}
