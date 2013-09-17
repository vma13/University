#include <stdio.h>

int main(int argc, char** argv) {
  unsigned int count;
  int last_elem, cur_elem;
  _Bool flag = 0;
  count = last_elem = 0;
  while( scanf("%d", &cur_elem)!= EOF ) {
    if( cur_elem < last_elem ) {
      if( flag ) count++;
      flag = 0;
    }
    else if( cur_elem == last_elem )
      count++;
    else 
     flag = 1;
    last_elem = cur_elem;
  }
  if( cur_elem <= last_elem && flag )
    count++;
  printf("Number of local maximum: %u\n", count);
  while(1);
  return 0;
}
