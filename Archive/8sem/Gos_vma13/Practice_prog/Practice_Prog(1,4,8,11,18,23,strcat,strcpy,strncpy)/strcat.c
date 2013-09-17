#include <stdio.h>
#include <malloc.h>

extern char *strcat(char*, const char*);

int main(int argc, char **argv) {
  char *dst = (char*)malloc(10*sizeof(char));
  *dst = 'a';
  char *src = "12322";
  printf("%s\n", strcat(dst, src));
  return 0;
}
