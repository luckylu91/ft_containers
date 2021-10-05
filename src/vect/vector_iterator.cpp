#include "test_vector.hpp"

void test_iterator_types() {
  vector<int> intVect;
  for (int i = 0; i < 10; i++)
    intVect.push_back(i);

  std::cout << "Mutable iterator" << std::endl;
  for (vector<int>::iterator it = intVect.begin(); it != intVect.end(); ++it)
    std::cout << *it << ", ";
  std::cout << "END" << std::endl;

  std::cout << "Mutable reverse iterator" << std::endl;
  for (vector<int>::reverse_iterator it = intVect.rbegin(); it != intVect.rend(); ++it)
    std::cout << *it << ", ";
  std::cout << "END" << std::endl;

  vector<int> const cIntVect(intVect);
  std::cout << "Const iterator" << std::endl;
  for (vector<int>::const_iterator it = cIntVect.begin(); it != cIntVect.end(); ++it)
    std::cout << *it << ", ";
  std::cout << "END" << std::endl;

  std::cout << "Reverse const iterator" << std::endl;
  for (vector<int>::const_reverse_iterator it = cIntVect.rbegin(); it != cIntVect.rend(); ++it)
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
  std::cout << "(it + 3) - it = " << (it + 3) - it << std::endl;
}

void test_comparison_iters() {
  vector<int> intVect;
  for (int i = 0; i < 10; i++)
    intVect.push_back(i);
  vector<int> const & cIntVect = intVect;

  std::cout << "begin() == (const_iterator)begin() : " << (intVect.begin() == cIntVect.begin()) << std::endl;
  std::cout << "(const_iterator)begin() == begin() : " << (cIntVect.begin() == intVect.begin()) << std::endl;
  std::cout << "end() == (const_iterator)end() : " << (intVect.end() == cIntVect.end()) << std::endl;
  std::cout << "(const_iterator)end() == end() : " << (cIntVect.end() == intVect.end()) << std::endl;
  std::cout << "begin() == (const_iterator)end() : " << (intVect.begin() == cIntVect.end()) << std::endl;
  std::cout << "(const_iterator)begin() == end() : " << (cIntVect.begin() == intVect.end()) << std::endl;
  std::cout << "end() == (const_iterator)begin() : " << (intVect.end() == cIntVect.begin()) << std::endl;
  std::cout << "(const_iterator)end() == begin() : " << (cIntVect.end() == intVect.begin()) << std::endl;
  std::cout << "begin() < (const_iterator)end() : " << (intVect.begin() < cIntVect.end()) << std::endl;
  std::cout << "(const_iterator)begin() < end() : " << (cIntVect.begin() < intVect.end()) << std::endl;
}

void test() {
  vector<int> intVect;
  for (int i = 0; i < 10; i++)
    intVect.push_back(i);
  vector<int> const cIntVect(intVect);

  std::boolalpha(std::cout);
  std::cout << "vector::iterator" << std::endl << std::endl;
  test_iterator_methods(intVect.begin());
  std::cout << std::endl;
  std::cout << "vector::const_iterator" << std::endl << std::endl;
  test_iterator_methods(cIntVect.begin());

  std::cout << std::endl;
  test_iterator_types();

  std::cout << std::endl;
  test_comparison_iters();
}
