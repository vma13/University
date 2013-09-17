#include <stdio.h>
struct R2Point{
  int x,y;
}

int main(void){
  struct R2Point p1;
    printf("p1.x->");scanf("%d", &p1.x);
    printf("p2.y->");scanf("%d", &p1.y);  
    p1.x+=5;
    p1.y-=10;
    printf("p1=(%d;%d)\n", p1.x, p1.y);
  
}
