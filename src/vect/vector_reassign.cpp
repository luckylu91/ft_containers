#include "test_vector.hpp"

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
    std::cout << "Assign Operator (" << _cpt << " becomes " << other._cpt << ")" << std::endl;
    _cpt = other._cpt;
    delete m;
    m = new int(*(other.m));
    return *this;
  }
  friend std::ostream & operator<<(std::ostream & os, A const & a) { os << "A(" << a._cpt << ")"; return os; }
};

int A::_ccpt = 0;


void test()
{
  // test2();
  vector<A> vect;

  std::cout << "--- reserving 25 ---" << std::endl;
  vect.reserve(25);
  std::cout << "--- push_back x 20 ---" << std::endl;
  for (int i = 0; i < 20; ++i) {
    vect.push_back(A());
  }
  std::cout << "--- end of scope ---" << std::endl;
}
