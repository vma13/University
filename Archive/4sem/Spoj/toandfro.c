#include <stdio.h>

int main(void) {
  char start[201], end[201];
  int num;
  int i, j, rows, x;
  while(1) {
    scanf("%d\n", &num);
    if( !num ) break;
    scanf("%s\n", &start);
    i = 0, j = 0;
    while( start[j] != '\0' )
      j++;
    rows = j/num;
    for(j = 1; j <= rows; j++) {
      int b;
      if(j%2 == 1) {
        for( b = 0; b < num; b++) {
          x = j + b*rows;
          end[x-1] = start[i];
          i++;
        }
      }
      else {
        for( b = num-1; b >= 0; b--) {
          x = j+b*rows;
          end[x-1] = start[i];
          i++;
        }
      }        
    }
    end[i] = '\0';
    printf("%s\n", end);
  }
  return 0;
}
