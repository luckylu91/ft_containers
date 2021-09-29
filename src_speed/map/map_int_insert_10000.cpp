#include "test_speed.hpp"

void test() {
	map<int, int> map_int;
  for (int i = 0; i < 10000; ++i) {
    map_int.insert(make_pair(rand(), rand()));
  }
}
