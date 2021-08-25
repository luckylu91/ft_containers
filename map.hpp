#pragma once
#include <memory>
#include "pair.hpp"

template <  class Key,                                     // map::key_type
            class T,                                       // map::mapped_type
            class Compare = std::less<Key>,                     // map::key_compare
            class Alloc = std::allocator<pair<const Key,T> >    // map::allocator_type
            > class map {
 public:
  class iterator;
  class const_iterator;
  class value_compare;
  class BST;

  typedef Key key_type;
  typedef T mapped_type;
  typedef pair<const key_type,mapped_type> value_type;
  typedef Compare key_compare;
  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename std::reverse_iterator<iterator> reverse_iterator;
  typedef typename std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef typename allocator_type::difference_type difference_type;
  typedef typename allocator_type::size_type size_type;

};

template <class Key, class T, class Compare, class Alloc>
class map<Key,T,Compare,Alloc>::value_compare
{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
  friend class map;
protected:
  Compare comp;
  value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
public:
  typedef bool result_type;
  typedef value_type first_argument_type;
  typedef value_type second_argument_type;
  bool operator() (const value_type& x, const value_type& y) const {
    return comp(x.first, y.first);
  }
};



