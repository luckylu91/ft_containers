#pragma once

#include <cstdlib>

template <class Container>
void print_container(Container const & m) {
  for (typename Container::const_iterator it = m.begin(); it != m.end(); ++it) {
    if (it != m.begin())
      std::cout << ", ";
    std::cout << *it;
  }
}
template <class Container>
void print_container_nl(Container const & m) {
  print_container(m);
  std::cout << std::endl;
}

template <class Iterator>
void print_all(Iterator first, Iterator last) {
  for (Iterator it = first; it != last; ++it) {
    if (it != first)
      std::cout << ", ";
    std::cout << *it;
  }
}
template <class Iterator>
void print_all_nl(Iterator first, Iterator last) {
  print_all(first, last);
  std::cout << std::endl;
}

template<typename T, size_t n>
size_t length(T (&)[n]) {
  return n;
}

template<typename T, size_t n>
T *array_end(T (&array)[n]) {
  return array + n;
}
