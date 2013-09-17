#ifndef DBL_VECTOR
#define DBL_VECTOR

class DblVector {
  friend std::ostream & operator<< (std::ostream&, DblVector &);
 private:
  double *_data;
  int _size, _capacity;
 public:
  DblVector(int n = 1);
  ~DblVector();
  void reserve(int);
  void put_at(int, double);
  void push_back(double);
  void insert(int, int, double);
  void print();
  void erase(int, int);
  void pop_back();
  int size();
  int capacity();
  double get_at(int);
};
#endif//

