#include <stdio.h>

extern char* add_a(char *);
int main (void) {
  char str[10]="chush";
  printf("%s\n", add_a(str));
  return 0;
}
  