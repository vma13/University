#include "Rational.h"
using std::cout;
using std::cin;
using std::endl;

int main(void) {
  Rational *r = new Rational();
  Rational *p = new Rational();
  cin >> *r >> *p;
  cout << *r << ", "  << *p << std::endl;
  cout << *r << " + " << *p << " = " << (*r + *p) << endl;
  cout << *r << " * " << *p << " = " << (*r * *p) << endl;
  cout << *r << " / " << *p << " = " << (*r / *p) << endl;
  cout << *r << " < " << *p << " = " << (*r < *p) << endl;
  cout << *r << " > " << *p << " = " << (*r > *p) << endl;
  cout << *r << " == " << *p << " = " << (*r == *p) << endl;
  cout << *r << " != " << *p << " = " << (*r != *p) << endl;
  cout << *r << " *r++" << " = " << (*r)++ << endl;
  cout << *r << " *r--" << " = " << (*r)-- << endl;
  return 0;
}
