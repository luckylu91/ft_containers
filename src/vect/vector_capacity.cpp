#include "test_vector.h"

void test() {
  std::boolalpha(std::cout);

  vector<int> vect_empty;
  std::cout << vect_empty.empty() << std::endl;

  int numbers[] = {9, 2, 5, 3, 0};
  vector<int> vect(numbers, numbers + sizeof(numbers) / sizeof(int));

  std::cout << vect.empty() << std::endl;
  std::cout << vect.size() << std::endl;

  vect.push_back(6);
  std::cout << vect.size() << std::endl;

  vect.resize(15, 666);
  print_vect(vect);

  vect.resize(5, 0);
  print_vect(vect);

  // size_t vect_size = vect.size();
  // size_t vect_capacity = vect.capacity();
  // for (size_t i = vect_size - 1; i < vect_capacity; ++i) {
  //   vect[i] = 999;
  // }
  // std::cout << (vect.capacity() == vect_capacity) << std::endl;


  std::cout << vect.max_size() << std::endl;
}
