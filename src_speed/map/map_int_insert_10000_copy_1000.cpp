#include "test_speed.hpp"

void test() {
  	map<int, int> map_int;
  for (int i = 0; i < 1000; ++i) {
    map_int.insert(make_pair(rand(), rand()));
  }
  for (int i = 0; i < 1000; ++i) {
    map<int, int> copy = map_int;
  }
}
