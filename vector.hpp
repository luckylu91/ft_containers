#pragma once
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <algorithm>

#define MIN_CAPACITY 5
#define RESIZE_MARGIN 10
#define RESERVE_MARGIN 10

namespace ft {

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

  explicit vector(const allocator_type &alloc = allocator_type())
      : _array(NULL), _size(0), _capacity(MIN_CAPACITY), _allocator(alloc) {
    _array = _allocator.allocate(MIN_CAPACITY);
  }

  explicit vector(size_type n, const value_type &val = value_type(),
                  const allocator_type &alloc = allocator_type())
      : _array(NULL), _size(n), _capacity(n), _allocator(alloc) {
    _array = _allocator.allocate(n);
    for (size_type i = 0; i < n; i++)
      _allocator.construct(_array + i, val);
  }

  template <class InputIterator>
  vector(InputIterator first, InputIterator last,
         const allocator_type &alloc = allocator_type())
      : _array(NULL), _size(0), _capacity(MIN_CAPACITY), _allocator(alloc) {
    _array = _allocator.allocate(MIN_CAPACITY);
    for (InputIterator it = first; it != last; ++it)
      push_back(*it);
  }

  vector(const vector &x) : _array(NULL), _size(x._size), _capacity(x._capacity), _allocator(x._allocator) {
    _copy(x);
  }

  ~vector() {
    if (_array != NULL)
      delete _array;
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
  // assign

  //Add element at the end (public member function )
  void push_back(const value_type &val) {
    if (_size == _capacity)
      _enlarge(_capacity * 2);
    _array[_size++] = val;
  }

  //Delete last element (public member function )
  void pop_back() {
    if (_size > 0) {
      _allocator.destroy(_array + _size);
      _size--;
    }
  }

  //Insert elements (public member function )
  // insert

  //Erase elements (public member function )
  // erase

  //Swap content (public member function )
  void swap(vector &x) {
    std::swap(*this, x);
  }

  //Clear content (public member function )
  void clear() {
    _destruct();
    _array = _allocator.allocate(MIN_CAPACITY);
    _capacity = MIN_CAPACITY;
  }

  //Construct and insert element (public member function )
  // emplace

  //Construct and insert element at the end (public member function )
  // emplace_back

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

  class iterator {
   public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::reference reference;

    iterator(pointer ptr = 0) : _ptr(ptr) {}
    iterator &operator=(iterator &x) {
      _ptr = x._ptr;
      return *this;
    }

    reference operator*() { return *_ptr; }
    reference operator->() { return _ptr; }
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
    typedef typename allocator_type::const_pointer pointer;
    typedef typename allocator_type::const_reference reference;

    const_iterator(pointer ptr = 0) : _ptr(ptr) {}
    const_iterator &operator=(const_iterator &x) {
      _ptr = x._ptr;
      return *this;
    }

    const_reference operator*() const { return *_ptr; }
    const_reference operator->() const { return _ptr; }
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
    value_type &operator[](int i) { return *(_ptr + i); }
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

  //Exchange contents of vectors
  friend void swap(vector<T, Alloc> &x, vector<T, Alloc> &y);

 private:
  pointer _array;
  size_type _size;
  size_type _capacity;
  Alloc _allocator;

  // DOUBT
  //
  void _destruct() {
    for (size_type i = 0; i < _size; i++)
      _allocator.destroy(_array + i);
    if (_array != NULL)
      _allocator.deallocate(_array, _capacity);
    _size = 0;
    _capacity = 0;
    _array = NULL;
  }

  void _copy(const vector<T, Alloc> &x) {
    _destruct();
    _array = _allocator.allocate(x._capacity);
    for (size_type i = 0; i < x._size; i++)
      _allocator.construct(_array + i, x[i]);
    _size = x._size;
    _capacity = x._capacity;
  }

  void _enlarge(size_type new_capacity) {
    pointer new_area = _allocator.allocate(new_capacity);
    pointer old_area = _array;
    if (_size > 0) {
      for (size_type i = 0; i < _size; i++)
        _allocator.construct(new_area + i, old_area[i]);
      _allocator.deallocate(old_area, _capacity);
    }
    _array = new_area;
    _capacity = new_capacity;
  }
};

template <class T, class Alloc>
void swap(vector<T, Alloc> &x, vector<T, Alloc> &y) {
  std::swap(x._array, y._array);
  std::swap(x._size, y._size);
  std::swap(x._capacity, y._capacity);
  std::swap(x._shrink_threshold, y._shrink_threshold);
  std::swap(x._allocator, y._allocator);
}

}  // namespace ft

