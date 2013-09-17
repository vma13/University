#include <iostream>

using namespace std;

/*class A{ 
public:
  A(){
    cout << "A();" << endl;
  }
      ~A(){
        cout << "~A();" << endl;
      }
};
int main(){
  cout << "begin \n";
  {A a;}
  cout << "end \n";
    return 0;
  }

*/
/*void f(int x, int y = 1, int z = 2){
  cout << "x =" << x << endl << "y =" << y << endl << "z =" << z << endl;
}

int main(){
  f(3);
  f(3,4);
  f(2,4,5);
  return 0;
 }
*/

/*class vector{
  int _x,_y;
  public:
    vector(){_x=0;_y=0;}
    vector(int xx,int yy){
      _x=xx;
      _y=yy;
      }
    vector& add(const vector& v){ // add -> operator += (const vector& v){
    _x+=v._x;
    _y+=v._y;
    return *this;
    }
    int x() {return _x;}
    int y() {return _y;}
  };

int main(){  
   vector a(1,2),b(3,4),c(5,6);
   a.add(b).add(c); // a += b += c;
   cout << "x = " << a.x() <<" ; "<<"y = "<< a.y()<< endl; 
   
return 0;  
}*/

class vector{
  int _x,_y;
  public:
    vector(){_x=0;_y=0;}
    vector(int xx,int yy){
      _x=xx;
      _y=yy;
      }
  vector& operator += (const vector& v){
    _x += v._x;
    _y += v._y;
    return *this;
   }
  vector& operator -= (const vector& f){
    _x -= f._x;
    _y -= f._y;
    return *this;
  }
  vector& operator *= (int tmp){
    cout << "Enter digit to multiplication";
    cin >> tmp;
    _x * tmp;
    _y * tmp;
    return *this;
  }
  vector& operator *= (const vector& h){
    _x * h._x + _y * h._y;
    return *this;
  }
  vector& operator == (const vector& j){
    if(_x == j._x && _y == j._y)
    cout << "Vectors are equal!";
    else
    cout << "Vectors are not equal!";
    return *this;
  }
  vector& operator != (const vector& k){
    if(_x != k._x || _y != k._y)
      cout << "Vectors are not same!";
    return *this;
  }
    int x() {return _x;}
    int y() {return _y;}
  };

int main(){  
  vector a(1,2),b(3,4),c(5,6);
 a += b += c;
 cout << "x = " << " " << a.x() << "y = " << a.y() << endl;
 a -= b -= c;
 cout << "x = " << " " << a.x() << "y = " << a.y() << endl;
 a *= b *= c;
 cout << "x = " << " " << a.x() << "y = " << a.y() << endl;
 a *= b *= c;
 cout << "x = " << " " << a.x() << "y = " << a.y() << endl;
 a == b == c;
 cout << "x = " << " " <<  a.x() << "y = " << a.y() << endl;
 a != b != c;
 cout << "x = " << " " << a.x() << "y = " << a.y() << endl; 
  return 0;  
}



  
