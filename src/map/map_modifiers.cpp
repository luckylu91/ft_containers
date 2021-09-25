#include "test_map.h"

void insert_many(map<int, int> & container, int n) {
  for (int i = 0; i < n; ++i) {
    container.insert(make_pair(i, i));
  }
}

void test_insert()
{
  map<int, int> m0;

  std::boolalpha(std::cout);
  for (int i = 0; i < 5; ++i) {
    insert(m0, i, i);
  }
  for (int i = 0; i < 5; ++i) {
    insert(m0, i, 2 * i);
  }

  insert_many(m0, 10000);
}

void test_clear() {
  srand(time(NULL));
  map<int, int> m;

  for (int i = 0; i < 1000 ; ++i) {
    m[i] = rand();
    if (i > 0)
      std::cout << ", ";
  }
  m.clear();
  print_container_nl(m);
  std::cout << m.size();
}

void test_swap() {
  map<int, int> m1, m2;

  for (int i = 0; i < 10; ++i) {
    m1[i] = i;
    m2[i] = 10 + i;
  }
  std::cout << "m1 = ";
  print_container_nl(m1);
  std::cout << "m2 = ";
  print_container_nl(m2);
  std::cout << "m1.swap(m2)..." << std::endl;
  m1.swap(m2);
  std::cout << "m1 = ";
  print_container_nl(m1);
  std::cout << "m2 = ";
  print_container_nl(m2);
  std::cout << "swap(m1, m2)..." << std::endl;
  swap(m1, m2);
  std::cout << "m1 = ";
  print_container_nl(m1);
  std::cout << "m2 = ";
  print_container_nl(m2);
}

void test_erase() {

}


void test() {
  test_insert();
  test_erase();
  test_swap();
  test_clear();
}
