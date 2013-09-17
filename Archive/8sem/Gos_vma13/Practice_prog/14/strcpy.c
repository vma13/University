#include <stdio.h>
#include <malloc.h>

extern char *strcpy(char*, const char*);

int main(int argc, char **argv) {
  char *dst = (char*)malloc(10*sizeof(char));
  *dst = '\0';
  char *src = "12322";
  printf("%s\n", strcpy(dst, src));
  return 0;
}
