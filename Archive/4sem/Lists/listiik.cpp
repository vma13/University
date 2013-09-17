#include <iostream>
#include <cmath>
using namespace std;

struct point {
  int x, y;
  static double dist(point p1, point p2);
  double dist2(point p);
};

void flip_horizontal(struct point *p){
  p->y = - p->y;

}

double point::dist2(point p){
  return sqrt(
              (this->x-p.x)*(this->x-p.x)+
              (this->y-p.y)*(this->y-p.y));
}


double point::dist(point p1, point p2){
  return sqrt(
              (p1.x-p2.x)*(p1.x-p2.x)+
              (p1.y-p2.y)*(p1.y-p2.y));
}



double rass(struct point p1,struct point p2){
  double n;
  n=sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
  return n;
}

  

int main(){
  struct point p1={0,3};
  struct point p2={4,0};
  cout << p1.dist2(p2) <<endl;
  return 0;
}



