#include "test_map.hpp"

void test() {
  map<int, int> m;

  for (int i = 0; i < 100; i++) {
    m[i] = i;
  }
  for (int i = 0; i < 100; i++) {
    std::cout << m[i] << " ";
  }
  std::cout << std::endl;
}
