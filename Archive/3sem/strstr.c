#include <stdio.h>
#include <string.h>

int main(void) {
  char *a = "abcbcd";
  char *b = "bcd";
  printf("%d\n", mystrstr(a, b));
  return 0;
}

int mystrstr(const char *haystack, const char *needle) {
  int i;
  int n = 0;
  int c = 0;
  int pos = 0;
  for (i = 0 ; haystack[i] != 0; i++) {
    if (haystack[i] == needle[n]) {
      c++;
      n++;
      if (c == strlen(needle)) {
        pos = i-strlen(needle)+1;
        return pos;
        break;
      }
    }
    else {
      c = 0;
      n = 0;
    }
  }
  return pos;
}
