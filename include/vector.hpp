#pragma once
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include "equal.hpp"
#include "lexicographical_compare.hpp"

//
#include <iostream>

#define MIN_CAPACITY 5
#define RESIZE_MARGIN 10
#define RESERVE_MARGIN 10
#define ASSIGN_MARGIN 10

namespace ft {

// true_type
struct true_type { static const bool value = true; };
struct false_type { static const bool value = false; };

// is_same
template <class U, class V> struct is_same : false_type {};
template <class U> struct is_same<U, U> : true_type {};

// enable_if
template <bool B> struct enable_if {};
template <> struct enable_if<true> { typedef void type; };

// enable_if_t
template <bool B, class T> struct enable_if_t {};
template <class T> struct enable_if_t<true, T> { typedef T type; };

template <typename T>
struct void_t_impl
{
  typedef void type;
};

template <typename Iter, typename = void>
  struct has_iterator_category
  : false_type {};
template <typename Iter>
  struct has_iterator_category <Iter, typename void_t_impl<typename Iter::iterator_category>::type >
  : true_type {};

template <typename Iter, typename Trait, typename = void>
  struct has_iterator_trait
  : false_type {};
template <typename Iter, typename Trait>
  struct has_iterator_trait<Iter, Trait, typename enable_if< is_same<typename Iter::iterator_category, Trait>::value >::type>
  : true_type {};

template <typename Iter, typename = void>
  struct is_iterator
  : false_type {};
template <typename Iter>
  struct is_iterator<
    Iter,
    typename enable_if<
        has_iterator_category<Iter>::value
        && ( has_iterator_trait<Iter, std::input_iterator_tag>::value ||
             has_iterator_trait<Iter, std::output_iterator_tag>::value ||
             has_iterator_trait<Iter, std::forward_iterator_tag>::value ||
             has_iterator_trait<Iter, std::bidirectional_iterator_tag>::value ||
             has_iterator_trait<Iter, std::random_access_iterator_tag>::value
        )
      >::type
  >
  : true_type {};

template <typename T, typename = void>
  struct is_integral
  : false_type {};
template <typename T>
  struct is_integral<
    T,
    typename enable_if<
      is_same<T, bool>::value ||
      is_same<T, char>::value ||
      is_same<T, signed char>::value ||
      is_same<T, unsigned char>::value ||
      is_same<T, wchar_t>::value ||
      is_same<T, short>::value ||
      is_same<T, unsigned short>::value ||
      is_same<T, int>::value ||
      is_same<T, unsigned int>::value ||
      is_same<T, long>::value ||
      is_same<T, unsigned long>::value
    >::type
  >
  : true_type {};

template <typename T, typename ValueAlloc = std::allocator<T> >
class vector {
 public:
  template <class IteratorType> class Iterator;

  typedef T                                              value_type;
  typedef ValueAlloc                                          allocator_type;
  typedef T&                                             reference;
  typedef const T&                                       const_reference;
  typedef T*                                             pointer;
  typedef typename allocator_type::size_type             size_type;
  typedef typename allocator_type::difference_type       difference_type;
  typedef const T*                                       const_pointer;
  typedef Iterator<value_type>                           iterator;
  typedef Iterator<const value_type>                     const_iterator;
  typedef typename std::reverse_iterator<iterator>       reverse_iterator;
  typedef typename std::reverse_iterator<const_iterator> const_reverse_iterator;

 private:
  struct _range {
    size_type       start;
    size_type       stop;
    difference_type increment;

    _range(size_type start, size_type stop, difference_type increment)
      : start(start), stop(stop), increment(increment) {}
  };

 public:
  // Constructors, Destructor, Assign operation

  /*explicit*/ vector(const allocator_type &alloc = allocator_type())
      : _array(NULL), _size(0), _capacity(MIN_CAPACITY), _allocator(alloc) {
    _allocate(MIN_CAPACITY);
  }

  /*explicit*/ vector(size_type n, const value_type &val = value_type(),
                  const allocator_type &alloc = allocator_type())
      : _array(NULL), _size(0), _capacity(n), _allocator(alloc) {
    _allocate(n);
    _construct(0, n, val);
  }

  template <class InputIterator>
  vector(InputIterator first,
        //  typename enable_if_t<is_iterator<InputIterator>::value, InputIterator>::type last,
         typename enable_if_t<!is_integral<InputIterator>::value, InputIterator>::type last,
         const allocator_type &alloc = allocator_type())
      : _array(NULL), _size(0), _capacity(MIN_CAPACITY), _allocator(alloc) {
    _allocate(MIN_CAPACITY);
    _push_back_range(first, last);
  }

  vector(const vector &x) : _array(NULL), _size(x._size), _capacity(x._capacity), _allocator(x._allocator) {
    _copy(x);
  }

  ~vector() {
    if (_array != NULL) {
      this->_destroy_from(0);
      this->_deallocate();
    }
  }

  vector &operator=(const vector &x) {
    _copy(x);
    return *this;
  }

  // Capacity

  //Return size (public member function )
  size_type size() const { return _size; }

  //Return maximum size (public member function )
  size_type max_size() const { return _allocator.max_size(); }

  //Change size (public member function )
  void resize(size_type n, value_type val = value_type()) {
    if (n < _size)
      _destroy_from(n);
    else if (n > _size) {
      if (n > _capacity)
        _enlarge(n + RESIZE_MARGIN);
      _construct(_size, n - _size, val);
    }
  }

  //Return size of allocated storage capacity (public member function )
  size_type capacity() const { return _capacity; }

  //Test whether vector is empty (public member function )
  bool empty() const { return _size == 0; }

  //Request a change in capacity (public member function )
  void reserve(size_type n) {
    if (_capacity < n)
      _enlarge(n + RESERVE_MARGIN);
  }

  // Element access

  //Access element (public member function )
  reference operator[](size_type n) { return _array[n]; };
  const_reference operator[](size_type n) const { return _array[n]; };

  //Access element (public member function )
  reference at(size_type n) {
    if (n >= _size)
      throw std::out_of_range("vector");
    return _array[n];
  }
  const_reference at(size_type n) const {
    if (n >= _size)
      throw std::out_of_range("vector");
    return _array[n];
  }

  //Access first element (public member function )
  reference front() { return _array[0]; }
  const_reference front() const { return _array[0]; }

  //Access last element (public member function )
  reference back() { return _array[_size - 1]; }
  const_reference back() const { return _array[_size - 1]; }

  // Modifiers

  //Assign vector content (public member function )
  template <class InputIterator>
      void assign(InputIterator first,
                  typename enable_if_t< !is_integral<InputIterator>::value, InputIterator >::type last) {
    _destroy_from(0);
    for (InputIterator it = first; it != last; ++it)
      push_back(*it);
  }

  void assign(size_type n, const value_type& val) {
    _destroy_from(0);
    if (n > _capacity)
    {
      _deallocate();
      _allocate(n + ASSIGN_MARGIN);
    }
    _construct(0, n, val);
  }

  //Add element at the end (public member function )
  void push_back(const value_type &val) {
    _enlarge_if_full();
    _construct(_size, 1, val);
  }

  //Delete last element (public member function )
  void pop_back() {
    if (_size > 0)
      _destroy_at(_size - 1);
  }

  //Insert elements (public member function )
  iterator insert(iterator position, const value_type& val) {
    return _insert_range(position, 1, val);
  }

  void insert(iterator position, size_type n, const value_type& val) {
    _insert_range(position, n, val);
  }

  template <class InputIterator>
    void insert (iterator position,
                 InputIterator first,
                 typename enable_if_t<!is_integral<InputIterator>::value, InputIterator>::type last) {
    while (first != last) {
      position = _insert_range(position, 1, *first);
      first++;
      position++;
    }
  }

  //Erase elements (public member function )
  iterator erase(iterator position) {
    erase(position, position + 1);
    return position;
  }

  iterator erase(iterator first, iterator last) {
    if (first >= begin() && first < last && last < end())
    {
      iterator first_mov = first;
      iterator last_mov = last;
      while (last_mov != end())
      {
        *first_mov = *last_mov;
        ++first_mov;
        ++last_mov;
      }
      _destroy_from(first_mov - begin());
    }
    return first;
  }

  //Swap content (public member function )
  void swap(vector &x) {
    std::swap(_array, x._array);
    std::swap(_size, x._size);
    std::swap(_capacity, x._capacity);
    std::swap(_allocator, x._allocator);
  }

  //Clear content (public member function )
  void clear() {
    _destroy_from(0);
    _deallocate();
    _allocate(MIN_CAPACITY);
  }

  // Allocator

  //Get allocator (public member function )
  allocator_type get_allocator() const { return _allocator; }

  // Non-member function overloads

  //Relational operators for vectors
  friend bool operator== (const vector<T,ValueAlloc>& lhs, const vector<T,ValueAlloc>& rhs) { return equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
  friend bool operator!= (const vector<T,ValueAlloc>& lhs, const vector<T,ValueAlloc>& rhs) { return !(lhs == rhs); }
  friend bool operator<  (const vector<T,ValueAlloc>& lhs, const vector<T,ValueAlloc>& rhs) { return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
  friend bool operator>  (const vector<T,ValueAlloc>& lhs, const vector<T,ValueAlloc>& rhs) { return lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()); }
  friend bool operator>= (const vector<T,ValueAlloc>& lhs, const vector<T,ValueAlloc>& rhs) { return !(lhs < rhs); }
  friend bool operator<= (const vector<T,ValueAlloc>& lhs, const vector<T,ValueAlloc>& rhs) { return !(lhs > rhs); }

  // Iterators

  //Return iterator to beginning
  iterator begin() { return iterator(_array); }
  const_iterator begin() const { return const_iterator(_array); }
  //Return iterator to end
  iterator end() { return _array != NULL ? iterator(_array + _size) : iterator(); }
  const_iterator end() const { return _array != NULL ? const_iterator(_array + _size) : const_iterator(); }
  //Return reverse iterator to reverse beginning
  reverse_iterator rbegin() { return _array != NULL ? reverse_iterator(_array + _size) : reverse_iterator(); }
  //Return reverse iterator to reverse end
  const_reverse_iterator rbegin() const { return _array != NULL ? const_reverse_iterator(_array + _size) : const_reverse_iterator(); }
  reverse_iterator rend() { return reverse_iterator(_array); }
  const_reverse_iterator rend() const { return const_reverse_iterator(_array); }

  //Exchange contents of vectors
  friend void swap(vector &x, vector &y) {
    x.swap(y);
  }


 private:
  pointer _array;
  size_type _size;
  size_type _capacity;
  ValueAlloc _allocator;

  void _allocate(size_type new_capacity) {
    _array = _allocator.allocate(new_capacity);
    _capacity = new_capacity;
    // _size = 0;
  }

  template <class InputIterator>
      void _push_back_range(InputIterator first, InputIterator last) {
    for (InputIterator it = first; it != last; ++it)
      push_back(*it);
  }

  void _construct(size_type start, size_type n, const value_type& val) {
    for (size_type i = 0; i < n; i++)
      _allocator.construct(_array + start + i, val);
    _size += n;
  }

  // void _construct_range(_range const & dst, _range const & src, size_type max) {
  //   size_type cpt = 0;
  //   size_type j = src.start;
  //   for (size_type i = dst.start; i != dst.stop && cpt < max; i += dst.increment) {
  //     _allocator.construct(_array + i, _array + j);
  //     j += src.increment;
  //     cpt++;
  //   }
  // }

  // void _copy_range(_range const & dst, _range const & src) {
  //   size_type j = src.start;
  //   for (size_type i = dst.start; i != dst.stop ; i += dst.increment) {
  //     *(_array + i) = *(_array + j);
  //     j += src.increment;
  //   }
  // }

  void _assign_range(_range const & dst, value_type const & val) {
    for (size_type i = dst.start; i != dst.stop ; i += dst.increment) {
      *(_array + i) = val;
    }
  }

  void _destroy_at(size_type i) {
    _allocator.destroy(_array + i);
    _size--;
  }

  void _destroy_from(size_type start) {
    for (size_type i = _size - 1; i != start - 1; i--)
      _allocator.destroy(_array + i);
    _size = start;
  }

  // DOUBT
  void _deallocate() {
    if (_array != NULL)
      _allocator.deallocate(_array, _capacity);
    _size = 0;
    _capacity = 0;
    _array = NULL;
  }

  void _copy(const vector<T, ValueAlloc> &x) {
    _destroy_from(0);
    _deallocate();
    _allocate(x._capacity);
    _push_back_range(x.begin(), x.end());
    _size = x._size;
  }

  void _enlarge(size_type new_capacity) {
    pointer new_area = _allocator.allocate(new_capacity);
    pointer old_area = _array;
    if (_size > 0) {
      for (size_type i = _size; i > 0; i--)
        _allocator.construct(new_area + i - 1, old_area[i - 1]);
      if (old_area != NULL) {
        for (size_type i = _size; i > 0; i--)
          _allocator.destroy(old_area + i - 1);
        _allocator.deallocate(old_area, _capacity);
      }
    }
    _array = new_area;
    _capacity = new_capacity;
  }

  void _enlarge_if_full(size_type delta = 1) {
      size_type new_capacity = _capacity;
      while (_size + delta > new_capacity)
        new_capacity *= 2;
      if (new_capacity > _capacity)
        _enlarge(new_capacity);
  }

  iterator _insert_range(iterator position, size_type n, value_type const & val) {
     size_type start = static_cast<size_type>(position - this->begin());
    _enlarge_if_full(n);
    // Move (part 1)
    size_type i = _size - 1 + n;
    while (i != _size - 1 && i != start + n - 1) {
      _allocator.construct(_array + i, _array[i - n]);
      i--;
    }
    // Move (part 2)
    while (i != start + n - 1) {
      _array[i] = _array[i - n];
      i--;
    }
    // Assign
    while (i != start - 1) {
      _array[i] = val;
      i--;
    }
    _size += n;
    return begin() + start;
  }

 public:
  template <class IteratorType>
  class Iterator {
   public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef std::ptrdiff_t                  difference_type;
    typedef IteratorType                    value_type;
    typedef ValueAlloc                           allocator_type;
    typedef IteratorType*                   pointer;
    typedef IteratorType&                   reference;

    Iterator(pointer ptr = 0) : _ptr(ptr) {}
    Iterator(Iterator const &x) : _ptr(x._ptr) {}
    Iterator &operator=(Iterator const &x) {
      _ptr = x._ptr;
      return *this;
    }
    ~Iterator() {}

    reference operator*() const { return *_ptr; }
    reference operator->() const { return _ptr; }
    Iterator &operator++() {
      ++_ptr;
      return *this;
    }
    Iterator operator++(int) {
      Iterator old_value(*this);
      ++_ptr;
      return old_value;
    }
    Iterator &operator--() {
      --_ptr;
      return *this;
    }
    Iterator operator--(int) {
      Iterator old_value(*this);
      --_ptr;
      return old_value;
    }
    value_type &operator[](int i) { return *(_ptr + i); }
    Iterator &operator+=(difference_type delta) {
      _ptr += delta;
      return *this;
    }
    Iterator &operator-=(difference_type delta) {
      _ptr -= delta;
      return *this;
    }

    friend difference_type operator-(Iterator const &a, Iterator const &b) { return a._ptr - b._ptr; };
    friend Iterator operator+(Iterator const &a, difference_type delta) { return Iterator(a._ptr + delta); };
    friend Iterator operator+(difference_type delta, Iterator const &a) { return Iterator(a._ptr + delta); };
    friend Iterator operator-(Iterator const &a, difference_type delta) { return Iterator(a._ptr - delta); };
    friend bool operator==(Iterator const &a, Iterator const &b) { return a._ptr == b._ptr; };
    friend bool operator!=(Iterator const &a, Iterator const &b) { return a._ptr != b._ptr; };
    friend bool operator<(Iterator const &a, Iterator const &b) { return a._ptr < b._ptr; };
    friend bool operator>(Iterator const &a, Iterator const &b) { return a._ptr > b._ptr; };
    friend bool operator<=(Iterator const &a, Iterator const &b) { return a._ptr <= b._ptr; };
    friend bool operator>=(Iterator const &a, Iterator const &b) { return a._ptr >= b._ptr; };

   private:
    pointer _ptr;
  };
};

}  // namespace ft

