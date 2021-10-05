#pragma once
#include "iterator_traits.hpp"

namespace ft {

template <class Iterator>
class reverse_iterator {
 public:
  typedef Iterator                                              iterator_type;
  typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
  typedef typename iterator_traits<Iterator>::value_type        value_type;
  typedef typename iterator_traits<Iterator>::difference_type   difference_type;
  typedef typename iterator_traits<Iterator>::pointer           pointer;
  typedef typename iterator_traits<Iterator>::reference         reference;

  reverse_iterator() : _base() {}
  explicit reverse_iterator (iterator_type it) : _base(it) {}
  template <class Iter> reverse_iterator (const reverse_iterator<Iter>& rev_it) : _base(rev_it._base) {}

  iterator_type base() const {
    return _base;
  };
  reference operator*() const {
    iterator_type tmp = _base;
    return *--tmp;
  }
  reverse_iterator operator+ (difference_type n) const {
    return reverse_iterator(_base - n);
  }
  reverse_iterator& operator++() {
    --_base;
    return *this;
  }
  reverse_iterator  operator++(int) {
    reverse_iterator tmp = *this;
    ++*this;
    return tmp;
  }
  reverse_iterator& operator+= (difference_type n) {
    _base -= n;
    return *this;
  }
  reverse_iterator operator- (difference_type n) const  {
    return reverse_iterator(_base + n);
  }
  reverse_iterator& operator--() {
    ++_base;
    return *this;
  }
  reverse_iterator  operator--(int) {
    reverse_iterator tmp = *this;
    --*this;
    return tmp;
  }
  reverse_iterator& operator-= (difference_type n) {
    _base += n;
    return *this;
  }
  pointer operator->() const {
    iterator_type tmp = _base;
    return (--tmp).operator->();
  }
  reference operator[] (difference_type n) const {
    return *(*this + n);
  }

  friend bool operator== (const reverse_iterator& lhs, const reverse_iterator& rhs) { return lhs._base == rhs._base; }
  friend bool operator!= (const reverse_iterator& lhs, const reverse_iterator& rhs) { return lhs._base != rhs._base; }
  friend bool operator<  (const reverse_iterator& lhs, const reverse_iterator& rhs) { return lhs._base > rhs._base; }
  friend bool operator<= (const reverse_iterator& lhs, const reverse_iterator& rhs) { return lhs._base >= rhs._base; }
  friend bool operator>  (const reverse_iterator& lhs, const reverse_iterator& rhs) { return lhs._base < rhs._base; }
  friend bool operator>= (const reverse_iterator& lhs, const reverse_iterator& rhs) { return lhs._base <= rhs._base; }
  friend difference_type operator- (const reverse_iterator& lhs, const reverse_iterator& rhs) { return rhs._base - lhs._base; }

 private:
  iterator_type _base;
};

} // namespace ft
