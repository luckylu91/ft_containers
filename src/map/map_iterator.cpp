#include "test_map.hpp"

void test_iterator_types() {
  map<int, int> bst;

  for (int i = 0; i < 15; ++i)
    bst.insert(make_pair(i, i));

  std::cout << "Mutable iterator" << std::endl;
  for (map<int, int>::iterator it = bst.begin(); it != bst.end(); ++it)
    std::cout << *it << ", ";
  std::cout << "END" << std::endl;

  std::cout << "Mutable reverse iterator" << std::endl;
  for (map<int, int>::reverse_iterator it = bst.rbegin(); it != bst.rend(); ++it)
    std::cout << *it << ", ";
  std::cout << "END" << std::endl;

  map<int, int> const cbst(bst);
  std::cout << "Const iterator" << std::endl;
  for (map<int, int>::const_iterator it = cbst.begin(); it != cbst.end(); ++it)
    std::cout << *it << ", ";
  std::cout << "END" << std::endl;

  std::cout << "Reverse const iterator" << std::endl;
  for (map<int, int>::const_reverse_iterator it = cbst.rbegin(); it != cbst.rend(); ++it)
    std::cout << *it << ", ";
  std::cout << "END" << std::endl;
}

// operator-> !
// Require size >= 3
template <class InputIterator>
void test_iterator_methods(InputIterator it) {
  std::cout << "*it = " << *it << std::endl;
  // operator++
  std::cout << "++it = " << *(++it) << ", now *it = " << *it << std::endl;
  // operator++(int)
  std::cout << "it++ = " << *(it++) << ", now *it = " << *it << std::endl;
  // operator--
  std::cout << "--it = " << *(--it) << ", now *it = " << *it << std::endl;
  // operator--(int)
  std::cout << "it-- = " << *(it--) << ", now *it = " << *it << std::endl;
  std::boolalpha(std::cout);
  // operator==
  std::cout << "it == it : " << (it == it) << std::endl;
  // operator!=
  std::cout << "it != it : " << (it != it) << std::endl;
  std::noboolalpha(std::cout);
}

void test() {
  map<int, int> bst;

  for (int i = 0; i < 15; ++i)
    bst.insert(make_pair(i, i));

  map<int, int> const cbst(bst);
  std::cout << "map::iterator" << std::endl << std::endl;
  test_iterator_methods(bst.begin());
  std::cout << std::endl;
  std::cout << "map::const_iterator" << std::endl << std::endl;
  test_iterator_methods(cbst.begin());

  test_iterator_types();
}
