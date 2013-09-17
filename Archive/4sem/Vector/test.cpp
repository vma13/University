#include <iostream>
#include "dbl_vector.h"
using std::cout;
using std::endl;

int main() {
  DblVector vect;
  cout << vect << endl;
  vect.push_back(1.2);
  cout << "push_back(1.2)\n" << vect << endl;
  vect.push_back(2.3);
  cout << "push_back(2.3)\n" << vect << endl;
  vect.push_back(3.4);
  cout << "push_back(3.4)\n" << vect << endl;
  vect.push_back(4.5);
  cout << "push_back(4.5)\n" << vect << endl;
  vect.insert(1, 2, 9.9);
  cout << "insert(1, 2, 9.9)\n" << vect << endl;
  vect.erase(2, 4);
  cout << "erase(2, 4)\n" << vect << endl;
  return 0;
}
