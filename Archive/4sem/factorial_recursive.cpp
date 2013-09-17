#include <iostream>
using namespace std;
int factorial(int x){
  if(x == 0) return 1;
  return x * factorial(x-1);
  cout << x << endl;
}
int main(){
  extern int x;
  cout << factorial(x) << endl;
}
