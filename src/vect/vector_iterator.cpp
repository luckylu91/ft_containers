#include <iostream>

#include "vector.hpp"

void test_iterator_types() {
  ft::vector<int> intVect;
  for (int i = 0; i < 10; i++)
    intVect.push_back(i);

  std::cout << "Mutable iterator" << std::endl;
  for (ft::vector<int>::iterator it = intVect.begin(); it != intVect.end(); ++it)
    std::cout << *it << ", ";
  std::cout << "END" << std::endl;

  std::cout << "Mutable reverse iterator" << std::endl;
  for (ft::vector<int>::reverse_iterator it = intVect.rbegin(); it != intVect.rend(); ++it)
    std::cout << *it << ", ";
  std::cout << "END" << std::endl;

  ft::vector<int> const cIntVect(intVect);
  std::cout << "Const iterator" << std::endl;
  for (ft::vector<int>::const_iterator it = cIntVect.begin(); it != cIntVect.end(); ++it)
    std::cout << *it << ", ";
  std::cout << "END" << std::endl;

  std::cout << "Reverse const iterator" << std::endl;
  for (ft::vector<int>::const_reverse_iterator it = cIntVect.rbegin(); it != cIntVect.rend(); ++it)
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
  ft::vector<int> intVect;
  for (int i = 0; i < 10; i++)
    intVect.push_back(i);
  ft::vector<int> const cIntVect(intVect);
  // test_iterator_types();
  std::cout << "vector::iterator" << std::endl << std::endl;
  test_iterator_methods(intVect.begin());
  std::cout << std::endl;
  std::cout << "vector::const_iterator" << std::endl << std::endl;
  test_iterator_methods(cIntVect.begin());
}