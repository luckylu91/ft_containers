#pragma once
#ifdef MINE
  #include "vector.hpp"
  using namespace ft;
#else
  #include <vector>
  using namespace std;
#endif
#include <iostream>
#include <typeinfo>
#include <exception>
#include <iomanip>

void test();

// template <class C1, class C2>
// std::ostream & operator<<(std::ostream & os, pair<C1, C2> const & p) {
//   os << "(" << p.first << "," << p.second << ")";
//   return os;
// }
