#include <stdio.h>

int str_len (char *str) {
  int len = 0;
  for (; *str != '\0'; len++) 
    str++;
  return len;
}

void swap(int* x, int* y){
  int z;
  z = *x;
  *x = *y;
  *y = z;
  
}

int str_cmp (char* str1, char* str2) {
  int i = 0;
  while (str1[i] - str2[i] == 0 && str1[i] != '\0') i++;
  return (str1[i]-str2[i]);
}

int str_cmp2 (const char* a, const char* b) {
  for (; *a == *b && *a != '\0'; a++, b++);
  return (*a - *b);
}

char* str_cpy (char* dest, const char* src) {
  int i = 0;
  while (dest[i] = src[i++]);
  return dest;
}

extern stlen (char *str);

int main () {
  char a[5] = "qwer";
  char b[5] = "qwer";
  printf("%d\n", stlen(a));
  int x = 2;
  int y = 3;
  swap(&x, &y);
  //printf("%d\n", stlen(a, b));
}


