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
  vector<T> vect;

  // push_back
  for (int i = 0; i < 10; i++) {
    vect.push_back(array10[i]);
    std::cout << vect.size() << std::endl;
    std::cout << vect.back() << std::endl;
  }
  print_vect_nl(vect);

  //insert iterator
  vect.insert(vect.begin() + 5, array7, array7 + 3);

  // insert 1
  typename vector<T>::iterator it = vect.insert(vect.begin(), array7[3]);
  std::cout << *it << std::endl;
  std::cout << it - vect.begin() << std::endl;
  *it = array7[4];

  // insert range
  vect.insert(vect.end() - 1, array7[5]);
  vect.insert(vect.begin() + 8, 6, array7[5]);

  print_vect_nl(vect);

  // pop_back
  for (int i = 0; i < 5; i++) {
    vect.pop_back();
    std::cout << "vect.back() = " << vect.back() << std::endl;
    std::cout << "vect.size() = " << vect.size() << std::endl;
  }
  print_vect_nl(vect);

  // erase, clear
  vect.erase(vect.begin() + 2);
  vect.clear();
}

template <typename T>
void test_assign(T (&array10)[10]) {
  vector<T> vect;

  vect.assign(array10, array10 + 10);
  std::cout << "vect.size() = " << vect.size() << std::endl;
  print_vect_nl(vect);

  vect.assign(array10, array10 + 5);
  std::cout << "vect.size() = " << vect.size() << std::endl;
  print_vect_nl(vect);

  vect.assign(100, array10[0]);
  std::cout << "vect.size() = " << vect.size() << std::endl;
  print_vect_nl(vect);

  vect.assign(5, array10[1]);
  std::cout << "vect.size() = " << vect.size() << std::endl;
  print_vect_nl(vect);
}

template <typename T>
void test_swap(T (&array10)[10], T (&array7)[7]) {
  vector<T> vect10;
  vector<T> vect7;

  vect10.assign(array10, array10 + 10);
  vect7.assign(array7, array7 + 7);
  print_vect_nl(vect10);
  print_vect_nl(vect7);
  std::cout << "Swapping" << std::endl;
  vect10.swap(vect7);
  print_vect_nl(vect10);
  print_vect_nl(vect7);
}


void test() {
  std::cout << "Test on vector<int>" << std::endl;
  int array10_int[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int array7_int[7] = {111, 222, 333, 444, 555, 666, 777};
  test_with<int>(array10_int, array7_int);
  test_assign<int>(array10_int);
  test_swap<int>(array10_int, array7_int);

  std::cout << std::endl;

  std::cout << "Test on vector<A>" << std::endl;
  A array10_A[10];
  for (int i = 0; i < 10; i++) array10_A[i] = array10_int[i];
  A array7_A[7];
  for (int i = 0; i < 7; i++) array7_A[i] = array7_int[i];
  test_with<A>(array10_A, array7_A);
  test_assign<A>(array10_A);
  test_swap<A>(array10_A, array7_A);
}
