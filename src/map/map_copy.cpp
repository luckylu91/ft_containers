#include "test_map.hpp"

void test() {
  map<int, int> m;

  for (int i = 0; i < 1000; i++) {
    m[i] = i;
  }
  map<int, int> m_copy(m);
  print_container_nl(m_copy);

  map<int, int> m_assign;
  m_assign = m;
  print_container_nl(m_assign);

  // Make sure all was duplicated
  m.clear();
  print_container_nl(m_copy);
  print_container_nl(m_assign);
}
