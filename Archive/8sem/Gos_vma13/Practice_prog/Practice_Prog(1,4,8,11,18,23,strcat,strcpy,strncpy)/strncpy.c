#include <stdio.h>
#include <malloc.h>

extern char* asm_strncpy(char*, const char*, size_t);

int main(int argc, char **argv) {
  char *dst = (char*)malloc(40*sizeof(char));
  *dst = '\0';
  char *src = "1221312431242146823546513";
  printf("%s\n", asm_strncpy(dst, src, 40));
  return 0;
}

