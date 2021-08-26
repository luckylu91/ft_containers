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

// Construct map (public member function )
  // empty (1)
  explicit map(const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type());

  // range (2)
  template <class InputIterator>
    map(InputIterator first, InputIterator last,
         const key_compare& comp = key_compare(),
         const allocator_type& alloc = allocator_type());

  // copy (3)
  map(const map& x);

// Map destructor (public member function )
  ~map();

// Copy container content (public member function )
  map& operator= (const map& x);

// Iterators

  // Return iterator to beginning (public member function )
  iterator begin();
  const_iterator begin() const;
  // Return iterator to end (public member function )
  iterator end();
  const_iterator end() const;
  // Return reverse iterator to reverse beginning (public member function )
  reverse_iterator rbegin();const_reverse_iterator rbegin() const;
  // Return reverse iterator to reverse end (public member function )
  reverse_iterator rend();const_reverse_iterator rend() const;

// Capacity

  // Test whether container is empty (public member function )
  bool empty() const;
  // Return container size (public member function )
  size_type size() const;
  // Return maximum size (public member function )
  size_type max_size() const;

// Element access

  // Access element (public member function )
  mapped_type& operator[] (const key_type& k);

// Modifiers

  // Insert elements (public member function )
  pair<iterator,bool> insert (const value_type& val);
  iterator insert (iterator position, const value_type& val);
  template <class InputIterator>  void insert (InputIterator first, InputIterator last);
  // Erase elements (public member function )
  void erase (iterator position);
  size_type erase (const key_type& k);
  void erase (iterator first, iterator last);
  // Swap content (public member function )
  void swap (map& x);
  // Clear content (public member function )
  void clear();

// Observers

  // Return key comparison object (public member function )
  key_compare key_comp() const;
  // Return value comparison object (public member function )
  value_compare value_comp() const;

// Operations

  // Get iterator to element (public member function )
  iterator find (const key_type& k);const_iterator find (const key_type& k) const;
  // Count elements with a specific key (public member function )
  size_type count (const key_type& k) const;
  // Return iterator to lower bound (public member function )
  iterator lower_bound (const key_type& k);const_iterator lower_bound (const key_type& k) const;
  // Return iterator to upper bound (public member function )
  iterator upper_bound (const key_type& k);const_iterator upper_bound (const key_type& k) const;
  // Get range of equal elements (public member function )
  pair<const_iterator,const_iterator> equal_range (const key_type& k) const;pair<iterator,iterator>             equal_range (const key_type& k);

// Allocator

  // Get allocator (public member function )
  allocator_type get_allocator() const;


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



