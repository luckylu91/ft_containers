#include "test_speed.hpp"

void test() {
  vector<int> vector_int;
  for (int i = 0; i < 100000; i++) {
    vector_int.push_back(rand());
  }
  for (int i = 0; i < 10000; i++) {
    vector_int.erase(vector_int.begin() + rand() % vector_int.size());
  }
}
