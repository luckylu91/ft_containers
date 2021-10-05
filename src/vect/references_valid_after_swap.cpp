#include "test_vector.hpp"

void test() {
  vector<int> vect1;
  vector<int> vect2;

  for (int i = 0; i < 10; i++) {
    vect1.push_back(i);
  }
  for (int i = 10; i < 20; i++) {
    vect2.push_back(i);
  }

  vector<int>::iterator it1 = vect1.begin() + 3;
  vector<int>::iterator it2 = vect2.begin() + 3;
  int* p1 = &vect1[4];
  int* p2 = &vect2[4];
  int& r1 = vect1[5];
  int& r2 = vect2[5];

  print_container_nl(vect1);
  print_container_nl(vect2);
  swap(vect1, vect2);
  print_container_nl(vect1);
  print_container_nl(vect2);

  std::cout << *it1 << std::endl;
  std::cout << *it2 << std::endl;
  std::cout << *p1 << std::endl;
  std::cout << *p2 << std::endl;
  std::cout << r1 << std::endl;
  std::cout << r2 << std::endl;
  *it1 = -1;
  *it2 = -2;
  *p1 = -3;
  *p2 = -4;
  r1 = -5;
  r2 = -6;
  print_container_nl(vect1);
  print_container_nl(vect2);
}
