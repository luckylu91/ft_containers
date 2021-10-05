#pragma once
#include "vector.hpp"

namespace ft {

template <class T, class Container = vector<T> >
struct stack {
  // Member types

  typedef T         value_type;
  typedef Container container_type;
  typedef size_t    size_type;



  // Member functions

  explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {}

  // Test whether container is empty (public member function )
  bool empty() const { return c.empty(); }

  // Return size (public member function )
  size_type size() const { return c.size(); }

  // Access next element (public member function )
  value_type& top() { return c.back(); }
  const value_type& top() const { return c.back(); }

  // Insert element (public member function )
  void push (const value_type& val) { c.push_back(val); }

  // Remove top element (public member function )
  void pop() { c.pop_back(); }

  friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs.c == rhs.c; }
  friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs.c != rhs.c; }
  friend bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs.c < rhs.c; }
  friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs.c <= rhs.c; }
  friend bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs.c > rhs.c; }
  friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs.c >= rhs.c; }

  // Member objects
 protected:
  container_type c;
};

} // namespace ft
