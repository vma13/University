#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
char *lookandsay(const char *s)
{
  int i, c, l, fi;
  char *r = NULL;
  char p;
 
  l = strlen(s);
  if ( l == 0 ) return NULL;
  r = malloc(l*3); /* worst case considered: each number gets a two digit counter */
  memset(r, 0, l*3);
  p = s[0];
  fi = 0;
  c = 1;
  for(i=1; i < l; i++) {
    if ( p == s[i] ) {
      c++;
    } else {
      fi += sprintf(&r[fi], "%d%c", c, p);
      c = 1;
      p = s[i];
    }
  }
  fi += sprintf(&r[fi], "%d%c", c, p);
  r[fi] = 0;
  free(s);
  return r;
}
 
int main()
{
  int i;
  const char *laf = "10";
 
  printf("%s\n", laf);
  for(i=0; i < 10; i++) {
    laf = lookandsay(laf);
    printf("%s\n", laf);
  }
  free(laf);
 
  return 0;
}
