#include "test_vector.hpp"

void try_at(vector<int> & vect, size_t n) {

  try {
    vect.at(n);
    std::cout << "at(" << n << ") : success" << std::endl;
  }
  catch (std::exception & e) {
    std::cout << e.what() << std::endl;
  }
}

void test() {
  vector<int> vect(100, 0);

  for (int i = 0; i < 100; i++) {
    vect[i] = i;
  }
  print_container(vect);
  std::cout << std::endl;
  for (int i = 0; i < 100; i++) {
    std::cout << vect[i] << " ";
  }
  std::cout << std::endl;

  std::cout << vect.size() << std::endl;

  try_at(vect, 5);
  try_at(vect, 105);

  vect.front() = 1111111;
  vect.back() = 9999999;
  print_container(vect);

  vector<int> const vect2(vect);
  std::cout << vect2.back() << std::endl;
  std::cout << vect2.front() << std::endl;
}
