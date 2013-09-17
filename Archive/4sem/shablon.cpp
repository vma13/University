#include <iostream>
using std::cout;
using std::endl;
template <class T>
T max(T a, T b){
  return (a > b ? a : b);
}

int main(){
  double a = 35.4864864;
  double b = 84.1864641;
  cout << max<double>(a, b) << endl;
}


