#include <stdio.h>
#include <sring.h>
extern int copystring(char *qq);
int main(void){
  char* qq = "abc";
  printf("%d\n",copystring(qq));
  return 0;
}
