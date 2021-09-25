#include "test_map.h"

void test_int() {
  map<int, int, KeyCompareInt> m;

  for (int i = 0; i < 20; ++i)
    insert(m, i, i);

  for (int i = 0; i < 20; ++i)
    std::cout << m[i] << std::endl;
}

// void test_str() {
//   map<std::string, int, KeyCompareStr> m;

//   for (int i = 0; i < 20; ++i)
//     insert(m, std::to_string(i), i);

//   for (int i = 0; i < 20; ++i)
//     std::cout << m[std::to_string(i)] << std::endl;
// }

void test() {
  test_int();
  // test_str();
}
