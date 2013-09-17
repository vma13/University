#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>

class Rational {
  friend std::ostream& operator << (std::ostream&, Rational&);
  friend std::istream& operator >> (std::istream&, Rational&);
 private:
  int _num, _denom;
  void change();
  int pow(int, int);
  int nok(int, int);
  int nod(int, int);
  void reduce();
 public:
  Rational(int = 1, int = 1);
  Rational(const Rational&);
  Rational& operator = (const Rational&);
  Rational& operator + (const Rational&);
  Rational& operator - (const Rational&);
  Rational& operator * (const Rational&);
  Rational& operator / (const Rational&);
  Rational& operator += (const Rational&);
  Rational& operator -= (const Rational&);
  Rational& operator *= (const Rational&);
  Rational& operator /= (const Rational&);
  bool operator < (const Rational&) const;
  bool operator > (const Rational&) const;
  bool operator == (const Rational&) const;
  bool operator != (const Rational&) const;
  Rational& operator ++ ();
  Rational& operator ++ (int);
  Rational& operator -- ();
  Rational& operator -- (int);
  Rational& pow(int);
  inline Rational& abs();
};

#endif
