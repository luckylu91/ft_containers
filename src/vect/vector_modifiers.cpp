#include "test_vector.h"

struct A {
  A() {
    m = new int();
  }
  A(A const & x) {
    m = new int();
    *m = *x.m;
  }
  A & operator=(A const & x) {
    *m = *x.m;
    return *this;
  }
  A & operator=(int n) {
    *m = n;
    return *this;
  }
  ~A() {
    delete m;
  }

  friend std::ostream & operator<<(std::ostream & os, A const & a) {
    return os << *a.m;
  }

  int *m;
};

template <typename T>
void test_with(T (&array10)[10], T (&array7)[7]) {
  (void)array10;
  (void)array7;
  vector<T> vect;

  for (int i = 0; i < 10; i++) {
    vect.push_back(array10[i]);
    std::cout << vect.size() << std::endl;
    std::cout << vect.back() << std::endl;
  }
  print_vect_nl(vect);

  vect.insert(vect.begin() + 5, array7, array7 + 3);

  // vector<T>::iterator it = vect.insert(vect.begin(), array7[3]);
  // std::cout << *it << std::endl;
  // std::cout << it - vect.begin() << std::endl;
  // *it = array7[4];

  vect.insert(vect.end() - 1, array7[5]);
  vect.insert(vect.begin() + 8, 6, array7[5]);

  print_vect_nl(vect);

  for (int i = 0; i < 5; i++) {
    vect.pop_back();
    std::cout << vect.back() << std::endl;
    std::cout << vect.size() << std::endl;
  }
  print_vect_nl(vect);

  vect.erase(vect.begin() + 2);
  vect.clear();
}

void test() {
  std::cout << "Test on vector<int>" << std::endl;
  int array10_int[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int array7_int[7] = {000, 111, 222, 333, 444, 555, 666};
  test_with<int>(array10_int, array7_int);

  std::cout << std::endl;

  std::cout << "Test on vector<A>" << std::endl;
  A array10_A[10];
  for (int i = 0; i < 10; i++) array10_A[i] = array10_int[i];
  A array7_A[7];
  for (int i = 0; i < 7; i++) array7_A[i] = array7_int[i];
  test_with<A>(array10_A, array7_A);
}
