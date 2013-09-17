#include <iostream>
#include <math.h>
#include <cassert>

using namespace std;

double rasstoyanie(double ax, double ay, double bx, double by, double x, double y){
 return (x*(bx-ax)+y*(by-ay)) / sqrt(x*x + y*y);
}

double scalar(double ax, double ay, double bx, double by, double x, double y){
  return ((ax*bx*x) - (ay*by*y));
}

int main(){
  cout << endl << rasstoyanie(1.0, 2.0, 3.0, 4.0, 5.0, 0.0) << endl << endl;
  cout << endl << rasstoyanie(0.0, 0.0, 1.0, 0.0, 2.0, 0.0) << endl << endl;
  cout << endl << rasstoyanie(0.0, 0.0, 0.0, 5.0, 10.0, 0.0) << endl << endl;

  //cout << endl<< scalar(1.0,3.0,5.0,2.0,4.0,0.0) << endl << endl;
  
  assert(rasstoyanie(1.0, 2.0, 3.0, 4.0, 5.0, 0.0) == 2 );
  assert(rasstoyanie(0.0, 0.0, 1.0, 0.0, 2.0, 0.0) == 1 );
  //  assert(rasstoyanie(0.0, 0.0, 0.0, 5.0, 10.0, 0.0) == 10 );
  
  return 0;
}

