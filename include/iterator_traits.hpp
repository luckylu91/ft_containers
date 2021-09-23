#pragma once
#include <iterator>

template <class Iterator>
struct iterator_traits {
  typedef Iterator::iterator_category iterator_category;
  typedef Iterator::value_type        value_type;
  typedef Iterator::difference_type   difference_type;
  typedef Iterator::pointer           pointer;
  typedef Iterator::reference         reference;
};

template <class T>
struct iterator_traits<T*> {
  typedef std::random_access_iterator_tag iterator_category;
  typedef T                               value_type;
  typedef std::ptrdiff_t                  difference_type;
  typedef T*                              pointer;
  typedef T&                              reference;
};

template <class T>
struct iterator_traits<T const *> {
  typedef std::random_access_iterator_tag iterator_category;
  typedef T                               value_type;
  typedef std::ptrdiff_t                  difference_type;
  typedef T const *                       pointer;
  typedef T const &                       reference;
};
