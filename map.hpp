#pragma once
#include <memory>
#include "BST.hpp"
#include "pair.hpp"

namespace ft {

template <  class Key,                                     // map::key_type
            class T,                                       // map::mapped_type
            class KeyCompare = std::less<Key>,                     // map::key_compare
            class Alloc = std::allocator<pair<const Key,T> >    // map::allocator_type
            >
class map {
 public:
  template<class IteratorType> class Iterator;
  class value_compare;

  typedef Key key_type;
  typedef T mapped_type;
  typedef pair<const key_type,mapped_type> value_type;
  typedef KeyCompare key_compare;
  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef Iterator<mapped_type> iterator;
  typedef Iterator<const mapped_type> const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef typename allocator_type::difference_type difference_type;
  typedef typename allocator_type::size_type size_type;

  typedef BST<key_type, mapped_type, value_compare, allocator_type> bst_type;
  typedef BST<key_type, mapped_type, value_compare, allocator_type>::Node bst_node_type;

// Construct map (public member function )
  // empty (1)
  explicit map(const key_compare& kComp = key_compare(),
               const allocator_type& alloc = allocator_type())
    : _tree(BST(kComp, alloc)),
      _kComp(this->_tree->get_key_comparator()),
      _comp(this->_tree->get_value_comparator()),
      _alloc(this->_tree->get_allocator()) {}

  // range (2)
  template <class InputIterator>
    map(InputIterator first, InputIterator last,
         const key_compare& comp = key_compare(),
         const allocator_type& alloc = allocator_type())
    : _tree(BST(comp, alloc)),
      _comp(this->_tree->get_comparator()),
      _alloc(this->_tree->get_comparator()) {
    for (InputIterator it = first; it != last; ++it)
      this->insert(*it);
  }

  // copy (3)
  map(const map& x);

// Map destructor (public member function )
  ~map();

// Copy container content (public member function )
  map& operator= (const map& x);

// Iterators

  // Return iterator to beginning (public member function )
  iterator begin() { return iterator(*this, false); }
  const_iterator begin() const {return const_iterator(*this, false); }
  // Return iterator to end (public member function )
  iterator end() { return iterator(*this, true); }
  const_iterator end() const {return const_iterator(*this, true); }
  // Return reverse iterator to reverse beginning (public member function )
  reverse_iterator rbegin() { return reverse_iterator(*this, false); }
  const_reverse_iterator rbegin() const {return const_reverse_iterator(*this, false); }
  // Return reverse iterator to reverse end (public member function )
  reverse_iterator rend() { return reverse_iterator(*this, true); }
  const_reverse_iterator rend() const {return const_reverse_iterator(*this, true); }

// Capacity

  // Test whether container is empty (public member function )
  bool empty() const { return this->_tree->empty(); }
  // Return container size (public member function )
  size_type size() const;
  // Return maximum size (public member function )
  size_type max_size() const;

// Element access

  // Access element (public member function )
  mapped_type& operator[] (const key_type& k) {
    
  }

// Modifiers

  // Insert elements (public member function )
  pair<iterator,bool> insert (const value_type& val) {
    pair<bst_node_type*, bool> insertResult = this->_tree->insert(val);
    return make_pair(iterator(*this, insertResult.first), insertResult.second);
  }

  // MEILLEUR MOYEN ?
  iterator insert(iterator position, const value_type& val) {
    pair<bst_node_type*, bool> insertResult = this->_tree->insert(val);
    return iterator(*this, insertResult.first);
  }

  template <class InputIterator>  void insert(InputIterator first, InputIterator last) {
    for (InputIterator it = first; it != end; ++it) {
      insert(*it);
    }
  }

  // Erase elements (public member function )
  void erase (iterator position);

  size_type erase (const key_type& k) {
    this->_tree.remove(k);
  }

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
  iterator find (const key_type& k);
  const_iterator find (const key_type& k) const;
  // Count elements with a specific key (public member function )
  size_type count (const key_type& k) const;
  // Return iterator to lower bound (public member function )
  iterator lower_bound (const key_type& k);const_iterator lower_bound (const key_type& k) const;
  // Return iterator to upper bound (public member function )
  iterator upper_bound (const key_type& k);const_iterator upper_bound (const key_type& k) const;
  // Get range of equal elements (public member function )
  pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
  pair<iterator,iterator>             equal_range (const key_type& k);

// Allocator

  // Get allocator (public member function )
  allocator_type get_allocator() const { return this->_tree.get};

  class value_compare
  {   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
    friend class map;
  protected:
    KeyCompare comp;
    value_compare (KeyCompare c) : comp(c) {}  // constructed with map's comparison object
  public:
    typedef bool result_type;
    typedef value_type first_argument_type;
    typedef value_type second_argument_type;
    bool operator() (const value_type& x, const value_type& y) const {
      return comp(x.first, y.first);
    }
  };

  template <class IteratorType>
    class Iterator<IteratorType> {
   public:
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    typedef IteratorType value_type;
    typedef Alloc allocator_type;
    typedef IteratorType* pointer;
    typedef IteratorType& reference;
    typedef BST<value_type, value_compare, allocator_type> bst_type;
    typedef BST<value_type, value_compare, allocator_type>::Node node_type;

    Iterator(bst_type const & bst, bool isEnd) : bst(bst), isEnd(isEnd) {
      if (bst.root == NULL)
        this->current = NULL;
      else if (!isEnd)
        this->current = bst.root->leftmost_child();
      else
        this->current = bst.root->rightmost_child();
    }

    Iterator(bst_type &bst, node_type *node) : bst(bst), isEnd(false) {
      this->current = node;
    }

    Iterator &operator=(Iterator &x) {
      this->current = x.current;
      this->isEnd = isEnd;
      return *this;
    }

    reference operator*() const { return *current->get_value(); }
    reference operator->() const { return current->get_value(); }
    Iterator &operator++() {
      Node *n = this->current->next();
      if (n == NULL);
        this->isEnd = true;
      this->current = n;
      return *this;
    }
    Iterator operator++(int) {
      Iterator old_value(*this);
      this->operator++();
      return old_value;
    }
    Iterator &operator--() {
      this->current = this->current->previous();
      return *this;
    }
    Iterator operator--(int) {
      Iterator old_value(*this);
      this->operator--();
      return old_value;
    }
    friend bool operator==(Iterator const &a, Iterator const &b) { return a.current == b.current; };
    friend bool operator!=(Iterator const &a, Iterator const &b) { return a.current != b.current; };

   private:
    node_type *current;
    bst_type const & bst;
    bool isEnd;
  };

 private:
  BST<value_type, key_compare, value_compare, allocator_type> _tree;
  key_compare &_kComp;
  value_compare &_comp;
  allocator_type &_alloc;
};


}  // namespace ft

