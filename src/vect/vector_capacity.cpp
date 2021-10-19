#include "test_vector.hpp"

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
  print_container(vect);

  vect.resize(5, 0);
  print_container(vect);

  std::cout << vect.max_size() << std::endl;
}
