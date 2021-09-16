#pragma once
#ifdef MINE
  #include "map.hpp"
  using namespace ft;
#else
  #include <map>
  using namespace std;
#endif
#include <iostream>
#include <typeinfo>
#include <exception>

void test();

template <class C1, class C2>
std::ostream & operator<<(std::ostream & os, pair<C1, C2> const & p) {
  os << "(" << p.first << "," << p.second << ")";
  return os;
}
