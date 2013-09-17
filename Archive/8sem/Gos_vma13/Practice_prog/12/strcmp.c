#include <stdio.h>

int mystr(const char*, const char*);

extern int mystrcmp(char*, char*);

int main(void) {
  char *str1 = "Stro311";
  char *str2 = "Stro31112312";
  int res1 = mystrcmp(str1, str2);
  int res2 = strcmp(str1, str2);
  printf("%d\n%d\n", res1, res2);
  return 0;
}
