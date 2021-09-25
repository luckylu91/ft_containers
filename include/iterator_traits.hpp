#pragma once
#include <iterator>

template <class Iterator>
struct iterator_traits {
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type        value_type;
  typedef typename Iterator::difference_type   difference_type;
  typedef typename Iterator::pointer           pointer;
  typedef typename Iterator::reference         reference;
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
