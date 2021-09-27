#include "test_map.h"

struct StaticCounter {
  static int total;
  int idx;
  StaticCounter() { idx = StaticCounter::total++; }
  StaticCounter(StaticCounter const &) { idx = StaticCounter::total++; }
  StaticCounter & operator=(StaticCounter const &) { return *this; }
  ~StaticCounter() { StaticCounter::total--; }
};

int StaticCounter::total = 0;

void test_size()
{
  map<int, StaticCounter> m;
  for (int i = 0; i < 10; ++i) {
    m.insert(make_pair(i, StaticCounter()));
    std::cout << "Map size = " << m.size() << std::endl;
    std::cout << "Actual size = " << StaticCounter::total << std::endl;
  }
  for (int i = 0; i < 5; ++i) {
    m.erase(i);
    std::cout << "Map size = " << m.size() << std::endl;
    std::cout << "Actual size = " << StaticCounter::total << std::endl;
  }
  m.clear();
  std::cout << "Map size = " << m.size() << std::endl;
  std::cout << "Actual size = " << StaticCounter::total << std::endl;
}

// void test_max_size() {
//   map<int, int> m1;
//   std::cout << "(int, int) max size : " << m1.max_size() << std::endl;
//   map<int, long long int> m2;
//   std::cout << "(int, long long int) max size : " << m2.max_size() << std::endl;
//   map<long long int, long long int> m3;
//   std::cout << "(long long int, long long int) max size : " << m3.max_size() << std::endl;
// }

void test() {
  std::cout << "--- Test size ---" << std::endl;
  test_size();
  // std::cout << "--- Test size ---" << std::endl;
  // test_max_size();
}
