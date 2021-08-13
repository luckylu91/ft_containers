#pragma once
#include <memory>
#include "pair.hpp"

template < class T, class Alloc = std::allocator<T> >
class BST {
  typedef T value_type;
  typedef Alloc allocator_type;
  // typedef typename allocator_type::reference reference;
  // typedef typename allocator_type::const_reference const_reference;
  // typedef typename allocator_type::pointer pointer;
  // typedef typename allocator_type::const_pointer const_pointer;
  // typedef typename std::reverse_iterator<iterator> reverse_iterator;
  // typedef typename std::reverse_iterator<const_iterator> const_reverse_iterator;
  // typedef typename allocator_type::difference_type difference_type;
  // typedef typename allocator_type::size_type size_type;
 private:
  BST *_left;
  BST *_right;
  value_type _node;
 public:
  BST(value_type const & val, allocator_type const & alloc = allocator_type())
    : _left(NULL), _right(NULL), _node(val) {}

  void add(value_type const & val) {
    
  }
}
