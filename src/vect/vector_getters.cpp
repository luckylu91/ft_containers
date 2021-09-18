#include "test_vector.h"

void test() {
  int numbers[] = {9, 2, 5, 3, 0};
  vector<int> vect(numbers, numbers + sizeof(numbers) / sizeof(int));

  std::cout << vect.size() << std::endl;
}
