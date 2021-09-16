#include "test.h"

void test() {
  map<int, int> m0;
  std::cout << typeid(m0.key_comp()).name() << std::endl;
  std::cout << typeid(m0).name() << std::endl;
}

