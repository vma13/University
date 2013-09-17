#include <stdio.h>

extern char* eesd(char *);
int main (void) {
  char str[10]="hell";
  printf("%s\n", eesd(str));
  return 0;
}
  