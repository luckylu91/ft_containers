#include "test_speed.hpp"

void test() {
  	map<int, int> map_int;
  for (int i = 0; i < 10000; ++i) {
    map_int.insert(make_pair(rand(), rand()));
  }

  int sum = 0;
  for (int i = 0; i < 100000; i++) {
    int access = rand() % map_int.size();
    sum += map_int[access];
  }
}
