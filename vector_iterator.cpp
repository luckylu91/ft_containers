#include <iostream>

#include "vector.hpp"

void test_types() {
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

// operator*
// operator-> !
// operator++
// operator++(int)
// operator--
// operator--(int)
// operator[]
// operator+=
// operator-=
// operator-
// operator+
// operator+
// operator-
// operator==
// operator!=
// operator<
// operator>
// operator<=
// operator>=
// Require size >= 5
template <class InputIterator>
void test_methods(InputIterator it) {
  std::cout << "*it = " << *it<< std::endl;
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
  std::cout << "*(it - (it + 2)) = " << it - (it + 2) << std::endl;
  std::cout << "*(it - (it - 1)) = " << it - (it - 1) << std::endl;
  // operator==
  // operator!=
  // operator<
  // operator>
  // operator<=
  // operator>=
}

int main() {
  ft::vector<int> intVect;
  for (int i = 0; i < 10; i++)
    intVect.push_back(i);

  test_types();
  test_methods(intVect.begin());
}
