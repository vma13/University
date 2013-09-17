#include <stdio.h>
#include <string.h>

char* str_cat (char* dest,  char* src) {
	char *d, *s;
	for (d = dest; *d != '\0'; d++);
	for (s = src ; *s != '\0'; *(d++) = *(s++));
	return dest;
}

int main () {
	char a[7] = "qwe";
	char b[4] = "rty";
	str_cat (a, b);
	printf ("%s\n", a);
	printf ("%s\n", b);
	printf ("%d\n", strlen(a));
}


