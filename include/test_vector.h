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

template<class T> void print_and_sep(T const &t) { std::cout << t << ", "; }
template<class Vect> void print_vect(Vect const &vect) {
  std::cout << "Vect(";
  for(typename Vect::const_iterator it = vect.begin(); it != vect.end() - 1; ++it)
    print_and_sep(*it);
  std::cout << *(vect.end() - 1) << ")";
}
template<class Vect> void print_vect_nl(Vect const &vect) {
  print_vect(vect);
  std::cout << std::endl;
}

template<typename T, size_t n>
size_t length(T (*)[n]) {
  return n;
}

template<typename T, size_t n>
int *end(T (*array)[n]) {
  return *array + n;
}

// template <class C1, class C2>
// std::ostream & operator<<(std::ostream & os, pair<C1, C2> const & p) {
//   os << "(" << p.first << "," << p.second << ")";
//   return os;
// }
