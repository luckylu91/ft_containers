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

void test()
{
  map<int, StaticCounter> m0;
  for (int i = 0; i < 10; ++i) {
    m0.insert(make_pair(i, StaticCounter()));
    std::cout << "Map size = " << m0.size() << std::endl;
    std::cout << "Actual size = " << StaticCounter::total << std::endl;
  }
  for (int i = 0; i < 5; ++i) {
    m0.erase(i);
    std::cout << "Map size = " << m0.size() << std::endl;
    std::cout << "Actual size = " << StaticCounter::total << std::endl;
  }
  m0.clear();
  std::cout << "Map size = " << m0.size() << std::endl;
  std::cout << "Actual size = " << StaticCounter::total << std::endl;
}
