// #include <vector>
#include "vector.hpp"
#include <iostream>

using namespace std;

class A {
  static int _ccpt;
  int _cpt;
  int *m;
 public:
  A() {
    _cpt = _ccpt++;
    m = new int;
    std::cout << "Constructor (" << _cpt << ")" << std::endl;
  }
  A(A const & other) {
    _cpt = other._cpt;
    m = new int(*(other.m));
    std::cout << "Copy Constructor (" << _cpt << ")" << std::endl;
  }
  ~A() {
    delete m;
    std::cout << "Destructor (" << _cpt << ")" << std::endl;
  }
  A & operator=(A const & other) {
    std::cout << "Assign Operator (" << _cpt << "->" << other._cpt << ")" << std::endl;
    _cpt = other._cpt;
    delete m;
    m = new int(*(other.m));
    return *this;
  }
  friend ostream & operator<<(ostream & os, A const & a) { os << "A(" << a._cpt << ")"; return os; }
};

int A::_ccpt = 0;

template<class T> void print_and_sep(T const &t) { std::cout << t << ", "; }
template<class Vect> void print_vect(Vect const &vect) {
  std::cout << "Vect(";
  for_each(vect.begin(), vect.end() - 1, &print_and_sep<typename Vect::value_type>);
  std::cout << *(vect.end() - 1) << ")" << std::endl;
}

int main()
{
  ft::vector<A> vect;

  vect.push_back(A());
  vect.push_back(A());
  vect.push_back(A());
  vect.push_back(A());
  std::cout << "vect : " << std::endl;
  print_vect(vect);
  std::cout << "erase :" << std::endl;
  vect.erase(vect.begin(), vect.begin() + 2);
  std::cout << "vect : " << std::endl;
  print_vect(vect);
  std::cout << "end" << std::endl;
}
