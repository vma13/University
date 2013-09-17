#include "Rational.h"
#include <cstdlib>

Rational::Rational(int a, int b): _num(a), _denom(b) {}

Rational::Rational(const Rational &r): _num(r._num), _denom(r._denom) {} 

std::ostream& operator << (std::ostream &os, Rational &r) {
  r.reduce();
  os << r._num;
  if( r._denom != 1 )
    os << "/" << r._denom;
  return os;
}

std::istream& operator >> (std::istream &is, Rational &r) {
  is >> r._num;
  is.ignore();
  is >> r._denom;
  if( r._denom == 0 ) {
    std::cerr << "Eror: Division by Zero.";
    exit( 1 );
  }
  r.change();
  return is;
}

Rational& Rational::operator = (const Rational &r) {
  _num = r._num;
  _denom = r._denom;
  return *this;
}


Rational& Rational::operator + (const Rational &r) {
  Rational *tmp = new Rational(*this);
  return *tmp += r;
}

Rational& Rational::operator += (const Rational &r) {
 if( _denom == r._denom )
    _num += r._num;
 else {
   int tmp = nok(_denom, r._denom);
   _num = _num*(tmp/_denom) + r._num*(tmp/r._denom);
   _denom = tmp;
 }
 return *this;
}

Rational& Rational::operator - (const Rational &r) {
 Rational *tmp = new Rational(*this);
 return *tmp -= r;
}

Rational& Rational::operator -= (const Rational &r) {
  if( _denom == r._denom )
    _num -= r._num;
  else {
    int tmp = nok(_denom, r._denom);
    _num = _num*(tmp/_denom) - r._num*(tmp/r._denom);
    _denom = tmp;
  }
  return *this;
}

Rational& Rational::operator * (const Rational &r) {
  Rational *tmp = new Rational(*this);
  return *tmp *= r;
}

Rational& Rational::operator *= (const Rational &r) {
  _num *= r._num;
  _denom *= r._denom;
  return *this;
}

Rational& Rational::operator / (const Rational &r) {
  Rational *tmp = new Rational(*this);
  return *tmp /= r;
}

Rational& Rational::operator /= (const Rational &r) {
  _num *= r._denom;
  _denom *= r._num;
  this->change();
  return *this;
}

bool Rational::operator < (const Rational &r) const{
  if( _denom == r._denom ) 
    return _num < r._num;
  else
    return _num*r._denom < r._num*_denom;
}

bool Rational::operator > (const Rational &r) const{
  if( _denom == r._denom ) 
    return _num > r._num;
  else
    return _num*r._denom > r._num*_denom;
}

bool Rational::operator == (const Rational &r) const{
  if( _denom == r._denom ) 
    return _num == r._num;
  else
    return _num*r._denom == r._num*_denom;
}

bool Rational::operator != (const Rational &r) const{
  return !(*this == r);
}

Rational& Rational::operator ++ () {
  _num += _denom;
  return *this;
}

Rational& Rational::operator ++ (int) {
  _num += _denom;
  return *this;
}

Rational& Rational::operator -- () {
  _num -= _denom;
  return *this;
}

Rational& Rational::operator -- (int) {
  _num -= _denom;
  return *this;
}

inline Rational& Rational::abs() {
  if( _num < 0 ) _num = std::abs(_num);
  return *this;
}

Rational& Rational::pow(int degree) {
  _num = pow(_num, degree);
  _denom = pow(_denom, degree);
  return *this;
}

int Rational::pow(int num, int degree) {
  int res = 1;
  while( degree ) {
    if( degree & 1) res *= num;
    num *= num;
    degree >>= 1;
  }
  return res;
}

int Rational::nok(int a, int b) {
  return a*b/nod(a, b);
}

int Rational::nod(int n, int m) {
  if( n == 0 || m == 0 ) return 0;
  int a = std::abs(n);
  int b = std::abs(m);
  while( a != 0 && b != 0) {
    if( a >= b ) a %= b;
    else b %= a;
  }
  return a + b; 
}

void Rational::reduce() {
  int tmp = nod(_num, _denom);
  if( tmp ) {
    _num /= tmp;
    _denom /= tmp;
  } 
  else _num = _denom = 0;
}

void Rational::change() {
  if( _denom < 0 ) {
    _num = -_num;
    _denom = std::abs(_denom);
  }
}
