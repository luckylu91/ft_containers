#include <iostream>
#include "map.hpp"

typedef ft::map<int, int> intBST;

void test_iterator_types() {
  intBST bst;

  for (int i = 0; i < 15; ++i)
      bst.insert(i);

  std::cout << "Mutable iterator" << std::endl;
  for (intBST::iterator it = bst.begin(); it != bst.end(); ++it)
    std::cout << *it << ", ";
  std::cout << "END" << std::endl;

  std::cout << "Mutable reverse iterator" << std::endl;
  for (intBST::reverse_iterator it = bst.rbegin(); it != bst.rend(); ++it)
    std::cout << *it << ", ";
  std::cout << "END" << std::endl;

  intBST const cbst(bst);
  std::cout << "Const iterator" << std::endl;
  for (intBST::const_iterator it = cbst.begin(); it != cbst.end(); ++it)
    std::cout << *it << ", ";
  std::cout << "END" << std::endl;

  std::cout << "Reverse const iterator" << std::endl;
  for (intBST::const_reverse_iterator it = cbst.rbegin(); it != cbst.rend(); ++it)
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
  // operator--
  std::cout << "it-- = " << *(it--) << ", now *it = " << *it << std::endl;
  // operator[]
  std::cout << "it[0] = " << it[0] << ", it[2] = " << it[2] << std::endl;
  // operator+=
  std::cout << "it += 2, now *it = " << *(it += 2) << std::endl;
  // operator-=
  std::cout << "it -= 1, now *it = " << *(it -= 1) << std::endl;
  // operator-
  std::cout << "*(it - 1) = " << *(it - 1) << std::endl;
  // operator+
  std::cout << "*(it + 1) = " << *(it + 1) << std::endl;
  // operator+
  std::cout << "*(1 + it) = " << *(1 + it) << std::endl;
  // operator-
  std::cout << "*(it - (it + 2)) = " << (it - (it + 2)) << std::endl;
  std::cout << "*(it - (it - 1)) = " << (it - (it - 1)) << std::endl;
  std::boolalpha(std::cout);
  // operator==
  std::cout << "it == it : " << (it == it) << std::endl;
  std::cout << "it == (it + 1) : " << (it == (it + 1)) << std::endl;
  // operator!=
  std::cout << "it != (it + 1) : " << (it != (it + 1)) << std::endl;
  std::cout << "it != it : " << (it != it) << std::endl;
  // operator<
  std::cout << "it < it : " << (it < it) << std::endl;
  std::cout << "it < (it + 1) : " << (it < (it + 1)) << std::endl;
  // operator>
  std::cout << "it > it : " << (it > it) << std::endl;
  std::cout << "it > (it - 1) : " << (it > (it - 1)) << std::endl;
  // operator<=
  std::cout << "it <= it : " << (it <= it) << std::endl;
  std::cout << "it <= (it + 1) : " << (it <= (it + 1)) << std::endl;
  // operator>=
  std::cout << "it >= it : " << (it >= it) << std::endl;
  std::cout << "it >= (it - 1) : " << (it >= (it - 1)) << std::endl;
  std::noboolalpha(std::cout);
}

int main() {
  intBST bst;

  for (int i = 0; i < 15; ++i)
      bst.insert(i);

  intBST const cbst(bst);
  // test_iterator_types();
  std::cout << "map::iterator" << std::endl << std::endl;
  test_iterator_methods(bst.begin());
  std::cout << std::endl;
  std::cout << "map::const_iterator" << std::endl << std::endl;
  test_iterator_methods(cbst.begin());
}
