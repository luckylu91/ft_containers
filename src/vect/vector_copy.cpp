#include "test_vector.hpp"

void test() {
  vector<int> vect;

  for (int i = 0; i < 1000; i++) {
    vect.push_back(i);
  }
  vector<int> vect_copy(vect);
  print_container_nl(vect_copy);

  vector<int> vect_assign;
  vect_assign = vect;
  print_container_nl(vect_assign);

  // Make sure all was duplicated
  vect.clear();
  print_container_nl(vect_copy);
  print_container_nl(vect_assign);
}
