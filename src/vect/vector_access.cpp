#include "test_vector.h"

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
  print_vect(vect);
  std::cout << std::endl;
  for (int i = 0; i < 100; i++) {
    std::cout << vect[i] << " ";
  }
  std::cout << std::endl;

  std::cout <<  << std::endl;
  std::cout << vect.size() << std::endl;

  try_at(vect, 5);
  try_at(vect, 105);
}
