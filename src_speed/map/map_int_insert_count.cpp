#include "test_speed.hpp"

void test() {
	map<int, int> map_int;
  for (int i = 0; i < COUNT; ++i) {
    map_int.insert(make_pair(rand(), rand()));
  }
}
