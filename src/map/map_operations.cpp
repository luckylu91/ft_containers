#include "test_map.h"

static map<int, int> m10;

void set_m10() {
  for (int i = 0; i < 10; ++i) {
    m10[i] = i;
  }
}

void test_find_replace(map<int, int> &m, int k, int r) {
  map<int, int>::iterator it = m.find(k);
  std::cout << k << " is in m : " << (it != m.end()) << std::endl;
  if (it != m.end())
    it->second = r;
  print_container_nl(m);
}

void test_find() {
  map<int, int> m = m10;
  test_find_replace(m, 1, 666);
  test_find_replace(m, 12, 0);
}

void test_count() {
  map<int, int> m = m10;
  std::cout << "Number of times 1 is present in m : " << m.count(1) << std::endl;
  std::cout << "Number of times 12 is present in m : " << m.count(12) << std::endl;
  print_container_nl(m);
}

void test_lower_bound() {
  map<int, int> m = m10;
  m.erase(3);

  std::cout << "lower_bound of 2 in m : ";
  print_all_nl(m.lower_bound(2), m.end());
  std::cout << "lower_bound of 3 in m : ";
  print_all_nl(m.lower_bound(3), m.end());
  std::cout << "lower_bound of 4 in m : ";
  print_all_nl(m.lower_bound(4), m.end());
}

void test_upper_bound() {
  map<int, int> m = m10;
  m.erase(3);

  std::cout << "upper_bound of 2 in m : ";
  print_all_nl(m.upper_bound(2), m.end());
  std::cout << "upper_bound of 3 in m : ";
  print_all_nl(m.upper_bound(3), m.end());
  std::cout << "upper_bound of 4 in m : ";
  print_all_nl(m.upper_bound(4), m.end());
}

void test_equal_range() {
  map<int, int> m = m10;
  m.erase(3);
  pair<map<int, int>::iterator, map<int, int>::iterator> range;

  range = m.equal_range(2);
  std::cout << "equal_range of 2 in m : ";
  print_all_nl(range.first, range.second);
  std::cout << "equal_range of 3 in m : ";
  range = m.equal_range(3);
  print_all_nl(range.first, range.second);
}

void test() {
  set_m10();
  std::boolalpha(std::cout);

  test_find();
  test_count();
  test_lower_bound();
  test_upper_bound();
  test_equal_range();
}
