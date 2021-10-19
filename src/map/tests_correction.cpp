#include "test_map.hpp"

void test_only_one_key() {
  map<std::string, std::string> m;

  m["chat"] = "chien";
  m["chat"] = "cheval";
  m["chat"] = "ça va ?";
  std::cout << "Map is of size " << m.size() << ": ";
  print_container_nl(m);
}

void test_container_ordered() {
  map<int, int> m;

  m[3] = 3;
  m[0] = 0;
  m[4] = 4;
  m[2] = 2;
  m[1] = 1;
  std::cout << "Should be ordered : ";
  print_container_nl(m);
}

void test_iterator_valid() {
  map<int, int> m;

  for (int i = 0; i < 5; ++i) {
    m[i] = i;
  }
  map<int, int>::iterator it = m.begin();
  ++it; ++it;
  std::cout << "Map is : ";
  print_container_nl(m);
  std::cout << "Iterator is ponting at " << *it << std::endl;
  std::cout << "Erasing keys 1 and 3" << std::endl;
  m.erase(1); m.erase(3);
  std::cout << "Iterator is ponting at " << *it << std::endl;
  std::cout << "it++;" << std::endl; it++;
  std::cout << "Iterator is ponting at " << *it << std::endl;
  std::cout << "it--; it--;" << std::endl; it--; it--;
  std::cout << "Iterator is ponting at " << *it << std::endl;
}

// struct MyInt {
//   MyInt(): ia(new int) {}
//   MyInt(MyInt const & x): ia(new int) {}
//   ~MyInt() { delete ia; }
//   MyInt & operator=(MyInt const & x) {}
//   int *ia;
// }

void test_swap_move_only_pointers() {
  map<int, int> m1;
  map<int, int> m2;
  pair<const int, int> *addr1;
  pair<const int, int> *addr2;

  m1[0] = 0;
  std::cout << "Before swap:" << std::endl;
  std::cout << "m1 = "; print_container(m1); std::cout << " and m2 = "; print_container_nl(m2);
  // std::cout << "Address of " << *m1.begin() << " : " << &*m1.begin() << std::endl;
  addr1 = &*m1.begin();
  m1.swap(m2);
  std::cout << "After swap:" << std::endl;
  std::cout << "m1 = "; print_container(m1); std::cout << "and m2 = "; print_container_nl(m2);
  // std::cout << "Address of " << *m2.begin() << " : " << &*m2.begin() << std::endl;
  addr2 = &*m2.begin();
  std::cout << "Address before and after are equal ? " << (addr1 == addr2) << std::endl;
}

void test() {
  std::boolalpha(std::cout);
  test_only_one_key();
  std::cout << std::endl;
  test_container_ordered();
  std::cout << std::endl;
  test_iterator_valid();
  std::cout << std::endl;
  test_swap_move_only_pointers();
}
