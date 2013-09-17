#include <iostream>
using std::cout;
template <class T, class S>

class Vector{
  S _size;
  T *_storage;
public:
  Vector(S size){ 
  _size = size;
  _storage = new T[size];
}
  Vector& put_at(int k, T x){
    _storage[k] = x; return *this;
  }
T get_at(int k){
  return _storage[k];
}
};

 int main(){
   Vector<double, int> v(10);
   for(int i = 0; i < 10; i++)
     v.put_at(i, i*10.525);
   for(int i = 0; i < 10; i++)
     cout << v.get_at(i) << " ";
   return 0;
 }


