#include <stdio.h>
extern int mystrcmp(char *s1, char *s2);
int main(void){
  printf("%d\n",mystrcmp("qq","qqq"));
  return 0;
}