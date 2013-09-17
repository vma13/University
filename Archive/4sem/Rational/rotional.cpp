#include <iostream>
#include <stdlib.h>

using namespace std;

class Rotional {
  int _ver, _niz;
public:
  Rotional() { _ver = 1; niz = 1; }
  Rotional(int ver, int niz) { _ver = ver; _niz = niz; }
  
  Rotional& operator+(const Rotional& v) {
    _ver += v._ver;
    _niz += v._niz;
    return *this;
  }
  /*
  Vector& operator-(const Vector& v) {
    _x -= v._x;
    _y -= v._y;
    return *this;
  }
  
  Vector& operator*=(int a){
    _x*=a;
    _y*=a;
    return *this;
    }
    
  int operator*=(const Vector& v){
  return _x*v._x+_y*v._y;  
  }

  bool operator==(const Vector& v){
  return _x==v._x && _y==v._y;
  }
  
  bool operator!=(const Vector& v){
  return _x!=v._x || _y!=v._y;
  }
  
  int x() { return _x;}
  int y() { return _y;}
};
*/
};
int main() {
  Rotional a(1/2),b(1/2);
  cout<< a.ver; 
  cout<< b.niz;
  //cout << "a*3 = (" << a.x() << ',' << a.y() << ")" << endl;
  //cout << (a==b) << endl;
  //cout << (a!=b) << endl;
  //cout << "a*b=" << (a*=b) << endl;
  return 0;
}
