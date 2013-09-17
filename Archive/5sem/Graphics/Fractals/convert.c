#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void test(int value) {
  if( value == -1 ) {
    fprintf(stderr, "%s\n", strerror(errno));
    exit( 1 );
  }
}

void read_file(FILE *f, char *buf) {
  fscanf(f, "%s", buf);
  test( fclose(f) );
}

int main(int argc, char **argv) {
  int iter, i, j, size;
  iter = (argc > 1) ? atoi(argv[1]): 1; 
  
  FILE *x, *y, *out;
  char x_buf[50] = {};
  char y_buf[50] = {};
  char a_buf[40000] = {0};
  
  x = fopen("X", "r");
  read_file(x, x_buf);
  
  y = fopen("Y", "r");
  read_file(y, y_buf);
  
  out = fopen("atom", "r");
  read_file(out, a_buf);
  size = strlen(a_buf);
  
  for(i = 0; i < iter; i++) {
    out = fopen("out", "w");
    for(j = 0; j < size; j++) {
      if(a_buf[j] == 'X') { 
        fprintf(out, "%s", x_buf);
        continue;
      }
      if(a_buf[j] == 'Y') {
        fprintf(out, "%s", y_buf);
        continue;
      }
      fprintf(out, "%c", a_buf[j]);
    }
    test( fclose(out) );
    out = fopen("out", "r");
    read_file(out, a_buf);
    size = strlen(a_buf);
  }
  return 0;
}
