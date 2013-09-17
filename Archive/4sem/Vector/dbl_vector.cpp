#include <iostream>
#include <cassert>
#include "dbl_vector.h"
using std::cout;
using std::endl;
using std::ostream;

ostream& operator << (ostream& stream, DblVector &v) {
  stream << "capacity = " << v.capacity() << "  size = " << v.size() << "  ";
  stream << "[";
  for( int i = 0; i < v._size; i++) {
    stream << v._data[i];
    if( i < v._size-1 ) stream << "; "; 
  }
  stream << "]\n";
  return stream;
}

DblVector::DblVector(int n) :_capacity(n), _size(0) {
  _data = new double[n];
  assert( _data != NULL );
}

void DblVector::reserve(int n) {
  _capacity += n;
  double *tmp = new double[_capacity];
  assert( tmp != NULL );
  for( int i = 0; i < _size; i++)
    tmp[i] = _data[i];
  delete[] _data;
  _data = tmp;
}

double DblVector::get_at(int i) {
  return ( i >= _size ) ? 0: _data[i-1];
}

void DblVector::push_back(double d) {
  if( _size == _capacity )  reserve(_capacity);
  _data[_size++] = d; 
}

void DblVector::print() {
  cout << "[";
  for( int i = 0; i < _size; i++) {
    cout << _data[i];
    if( i < _size-1 ) cout << "; "; 
  }
  cout << "]" << endl;
}

void DblVector::insert(int start, int times, double d) {
  if( _capacity <= _size+times ) {
    int num = 0;
    do 
      num += _capacity;
    while( _capacity+num <= _size+times );
    reserve(num);
  }
  for( int i = _size-1; i >= start; i--)
    _data[i+times] = _data[i];
  _size += times;
  for( int i = start; times > 0; i++, times--)
    _data[i] = d;
}

void DblVector::erase(int begin, int end) {
  for( int i = begin, j = end; j < _size; i++, j++)
    _data[i] = _data[j];
  _size -= (end-begin);
}

void DblVector::put_at(int j, double d) {
  insert(j, 1, d);
}

void DblVector::pop_back() { 
  if( _size >= 0) _size--;
}

DblVector::~DblVector() {
  delete[] _data;
}

int DblVector::size() { 
  return _size;
}

int DblVector::capacity() { 
  return _capacity;
}
