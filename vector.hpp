#pragma once
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <algorithm>

//
#include <iostream>

#define MIN_CAPACITY 5
#define RESIZE_MARGIN 10
#define RESERVE_MARGIN 10
#define ASSIGN_MARGIN 10

namespace ft {

// // enable_if
// template <bool B, typename T = void> struct enable_if {};
// template <typename T> struct enable_if<true, T> { typedef T type; };

// // is_same
// template<class T, class U>
// struct is_same {
//   static const bool value = false;
// };
// template<class T>
// struct is_same<T, T> {
//   static const bool value = true;
// };

// // is_iterator
// template<typename T, typename = void>
// struct is_iterator {
//    static const bool value = false;
// };
// template<typename T>
// struct is_iterator<T, typename enable_if<!is_same<typename T::iterator_category, void>::value, T>::type>
// {
//    static const bool value = true;
// };

// true_type
struct true_type { static const bool value = true; };
struct false_type { static const bool value = false; };

// is_same
template <class U, class V> struct is_same : false_type {};
template <class U> struct is_same<U, U> : true_type {};

// // is_iterator
// template <class Iter, class = void> struct is_iterator : false_type {};
// template <class Iter> struct is_iterator<Iter, typename Iter::iterator_category> : true_type {};

// // enable_if
// template <bool B, class T> struct enable_if {};
// template <class T> struct enable_if<true, T> { typedef T type; };

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
        && (   has_iterator_trait<Iter, std::input_iterator_tag>::value
            || has_iterator_trait<Iter, std::output_iterator_tag>::value
            || has_iterator_trait<Iter, std::forward_iterator_tag>::value
            || has_iterator_trait<Iter, std::bidirectional_iterator_tag>::value
            || has_iterator_trait<Iter, std::random_access_iterator_tag>::value
        )
      >::type
    >
  : true_type {};

template <typename T, typename Alloc = std::allocator<T> >
class vector {
 public:
  class iterator;
  class const_iterator;

  typedef T value_type;
  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename std::reverse_iterator<iterator> reverse_iterator;
  typedef typename std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef typename allocator_type::difference_type difference_type;
  typedef typename allocator_type::size_type size_type;

 public:
  // Constructors, Destructor, Assign operation

  /*explicit*/ vector(const allocator_type &alloc = allocator_type())
      : _array(NULL), _size(0), _capacity(MIN_CAPACITY), _allocator(alloc) {
    _allocate(MIN_CAPACITY);
  }

  /*explicit*/ vector(size_type n, const value_type &val = value_type(),
                  const allocator_type &alloc = allocator_type())
      : _array(NULL), _size(n), _capacity(n), _allocator(alloc) {
    _allocate(n);
    _construct(0, n, val);
  }

  template <class InputIterator>
  vector(InputIterator first,
         typename enable_if_t<is_iterator<InputIterator>::value, InputIterator>::type last,
         const allocator_type &alloc = allocator_type())
      : _array(NULL), _size(0), _capacity(MIN_CAPACITY), _allocator(alloc) {
    _allocate(MIN_CAPACITY);
    _construct(first, last);
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
    if (n < _size) {
      for (size_type i = n; i < _size; ++i)
        _allocator.destroy(_array + i);
    } else if (n > _size) {
      if (n > _capacity)
        _enlarge(n + RESIZE_MARGIN);
      for (size_type i = _size; i < n; ++i)
        _allocator.construct(_array + i, val);
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
      void assign (InputIterator first, InputIterator last) {
    _destroy_from(0);
    for (InputIterator it = first; it != last; ++it)
      push_back(*it);
  }

  void assign (size_type n, const value_type& val) {
    _destroy_from(0);
    if (n > _capacity)
    {
      _deallocate();
      _allocate(n + ASSIGN_MARGIN);
    }
    else if (n < _capacity)
      _destroy_from(n);
    _construct(0, n, val);
  }

  //Add element at the end (public member function )
  void push_back(const value_type &val) {
    // _enlarge_if_full();
    if (_size == _capacity)
      _enlarge(_capacity * 2);
    _allocator.construct(_array + _size++, val);
  }

  //Delete last element (public member function )
  void pop_back() {
    if (_size > 0)
      _destroy_at(_size);
  }

  //Insert elements (public member function )
  iterator insert(iterator position, const value_type& val) {
    if (position >= begin() && position < end())
      insert(position, 1, val);
  }

  void insert(iterator position, size_type n, const value_type& val) {
    _enlarge_if_full(n);
    size_type start = static_cast<size_type>(position - begin());
    size_type i = _size - 1 + n;
    while (i >= _size || i >= start + n) {
      _allocator.construct(_array + i, _array + i - n);
      i--;
    }
    while (i >= start + n) {
      *(_array + i) = *(_array + i - n);
      i--;
    }
    while (i >= start) {
      *(_array + i) = val;
      i--;
    }
  }

  template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last) {
      for (InputIterator it = first; it != last; ++it)
        insert(position++, *it);
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
    std::swap(*this, x);
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
  // bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
  // bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
  // bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
  // bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
  // bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
  // bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

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
  friend void swap(vector<T, Alloc> &x, vector<T, Alloc> &y);

 private:
  pointer _array;
  size_type _size;
  size_type _capacity;
  Alloc _allocator;

  void _allocate(size_type new_capacity) {
    _array = _allocator.allocate(new_capacity);
    _capacity = new_capacity;
    // _size = 0;
  }

  template <class InputIterator>
      void _construct(InputIterator first, InputIterator last) {
    for (InputIterator it = first; it != last; ++it)
      push_back(*it);
  }

  void _construct(size_type start, size_type n, const value_type& val) {
      for (size_type i = 0; i < n; i++)
        _allocator.construct(_array + start + i, val);
  }

  void _destroy_at(size_type i) {
    _allocator.destroy(_array + i);
    _size--;
  }

  void _destroy_from(size_type start) {
    for (size_type i = 0; i < _size - start; i++)
      _allocator.destroy(_array + start + i);
    _size = start;
  }

  // DOUBT
  //
  void _deallocate() {
    if (_array != NULL)
      _allocator.deallocate(_array, _capacity);
    _size = 0;
    _capacity = 0;
    _array = NULL;
  }

  void _copy(const vector<T, Alloc> &x) {
    _destroy_from(0);
    _deallocate();
    _allocate(x._capacity);
    _construct(x.begin(), x.end());
    _size = x._size;
  }

  void _enlarge(size_type new_capacity) {
    pointer new_area = _allocator.allocate(new_capacity);
    pointer old_area = _array;
    if (_size > 0) {
      for (size_type i = 0; i < _size; i++)
        _allocator.construct(new_area + i, old_area[i]);
      if (old_area != NULL) {
        for (size_type i = 0; i < _size; i++)
          _allocator.destroy(old_area + i);
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

  void swap(vector &x, vector &y) {
    std::swap(x._array, y._array);
    std::swap(x._size, y._size);
    std::swap(x._capacity, y._capacity);
    std::swap(x._shrink_threshold, y._shrink_threshold);
    std::swap(x._allocator, y._allocator);
  }

 public:
  class iterator {
   public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef Alloc allocator_type;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::reference reference;

    iterator(pointer ptr = 0) : _ptr(ptr) {}
    iterator &operator=(iterator &x) {
      _ptr = x._ptr;
      return *this;
    }

    reference operator*() const { return *_ptr; }
    reference operator->() const { return _ptr; }
    iterator &operator++() {
      ++_ptr;
      return *this;
    }
    iterator operator++(int) {
      iterator old_value(*this);
      ++_ptr;
      return old_value;
    }
    iterator &operator--() {
      --_ptr;
      return *this;
    }
    iterator operator--(int) {
      iterator old_value(*this);
      --_ptr;
      return old_value;
    }
    value_type &operator[](int i) { return *(_ptr + i); }
    iterator &operator+=(difference_type delta) {
      _ptr += delta;
      return *this;
    }
    iterator &operator-=(difference_type delta) {
      _ptr -= delta;
      return *this;
    }

    friend difference_type operator-(iterator const &a, iterator const &b) { return a._ptr - b._ptr; };
    friend iterator operator+(iterator const &a, difference_type delta) { return iterator(a._ptr + delta); };
    friend iterator operator+(difference_type delta, iterator const &a) { return iterator(a._ptr + delta); };
    friend iterator operator-(iterator const &a, difference_type delta) { return iterator(a._ptr - delta); };
    friend bool operator==(iterator const &a, iterator const &b) { return a._ptr == b._ptr; };
    friend bool operator!=(iterator const &a, iterator const &b) { return a._ptr != b._ptr; };
    friend bool operator<(iterator const &a, iterator const &b) { return a._ptr < b._ptr; };
    friend bool operator>(iterator const &a, iterator const &b) { return a._ptr > b._ptr; };
    friend bool operator<=(iterator const &a, iterator const &b) { return a._ptr <= b._ptr; };
    friend bool operator>=(iterator const &a, iterator const &b) { return a._ptr >= b._ptr; };

   private:
    pointer _ptr;
  };

  class const_iterator {
   public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef Alloc allocator_type;
    typedef typename allocator_type::const_pointer pointer;
    typedef typename allocator_type::const_reference reference;

    const_iterator(pointer ptr = 0) : _ptr(ptr) {}
    const_iterator &operator=(const_iterator &x) {
      _ptr = x._ptr;
      return *this;
    }

    reference operator*() const { return *_ptr; }
    reference operator->() const { return _ptr; }
    const_iterator &operator++() {
      ++_ptr;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator old_value(*this);
      ++_ptr;
      return old_value;
    }
    const_iterator &operator--() {
      --_ptr;
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator old_value(*this);
      --_ptr;
      return old_value;
    }
    reference operator[](int i) { return *(_ptr + i); }
    const_iterator &operator+=(difference_type delta) {
      _ptr += delta;
      return *this;
    }
    const_iterator &operator-=(difference_type delta) {
      _ptr -= delta;
      return *this;
    }

    friend difference_type operator-(const_iterator const &a, const_iterator const &b) { return a._ptr - b._ptr; };
    friend const_iterator operator+(const_iterator const &a, difference_type delta) { return const_iterator(a._ptr + delta); };
    friend const_iterator operator+(difference_type delta, const_iterator const &a) { return const_iterator(a._ptr + delta); };
    friend const_iterator operator-(const_iterator const &a, difference_type delta) { return const_iterator(a._ptr - delta); };
    friend bool operator==(const_iterator const &a, const_iterator const &b) { return a._ptr == b._ptr; };
    friend bool operator!=(const_iterator const &a, const_iterator const &b) { return a._ptr != b._ptr; };
    friend bool operator<(const_iterator const &a, const_iterator const &b) { return a._ptr < b._ptr; };
    friend bool operator>(const_iterator const &a, const_iterator const &b) { return a._ptr > b._ptr; };
    friend bool operator<=(const_iterator const &a, const_iterator const &b) { return a._ptr <= b._ptr; };
    friend bool operator>=(const_iterator const &a, const_iterator const &b) { return a._ptr >= b._ptr; };

   private:
    pointer _ptr;
  };
};

}  // namespace ft

