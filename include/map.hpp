#pragma once
#include <functional>
#include <memory>
// #include <cmath>
#include <algorithm>  // max

#include "pair.hpp"
// //
// #include <iostream>
// #include <iomanip>

namespace ft {

template <class Key,
          class T,
          class KeyCompare = std::less<Key>,
          class ValueAlloc = std::allocator<pair<const Key, T> > >
class map {
 public:
  struct value_compare;
  template <class ValueType, class NodeType> class Iterator;

 private:
  class BST;

 public:

  typedef Key                                             key_type;
  typedef T                                               mapped_type;
  typedef pair<const key_type, mapped_type>               value_type;
  typedef KeyCompare                                      key_compare;
  typedef ValueAlloc                                      allocator_type;
  typedef typename allocator_type::reference              reference;
  typedef typename allocator_type::const_reference        const_reference;
  typedef typename allocator_type::pointer                pointer;
  typedef typename allocator_type::const_pointer          const_pointer;
  typedef typename allocator_type::difference_type        difference_type;
  typedef typename allocator_type::size_type              size_type;
  typedef BST                                             bst_type;
  typedef typename BST::Node                              bst_node_type;
  typedef Iterator<value_type, bst_node_type>             iterator;
  typedef Iterator<const value_type, const bst_node_type> const_iterator;
  typedef std::reverse_iterator<iterator>                 reverse_iterator;
  typedef std::reverse_iterator<const_iterator>           const_reverse_iterator;

  // Constructor
  explicit map(const key_compare &kComp = key_compare(),
               const allocator_type &alloc = allocator_type())
      : _tree(kComp, alloc), _key_comp(kComp), _comp(kComp), _alloc(alloc) {}

  template <class InputIterator>
  map(InputIterator first, InputIterator last,
      const key_compare &kComp = key_compare(),
      const allocator_type &alloc = allocator_type())
    : _tree(kComp, alloc), _key_comp(kComp), _comp(kComp), _alloc(alloc) {
    for (InputIterator it = first; it != last; ++it)
      this->insert(*it);
  }

  map(const map &x)
      : _tree(x._tree), _key_comp(x._key_comp), _comp(x._comp), _alloc(x._alloc) {}

  // Destructor
  ~map() {}

  // Copy container content
  map &operator=(const map &x) {
    _tree = x._tree;
    return *this;
  }

  // Iterators

  iterator begin()                      { return iterator(*this, false); }
  const_iterator begin() const          { return const_iterator(*this, false); }
  iterator end()                        { return iterator(*this, true); }
  const_iterator end() const            { return const_iterator(*this, true); }
  reverse_iterator rbegin()             { return reverse_iterator(this->end()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }
  reverse_iterator rend()               { return reverse_iterator(this->begin()); }
  const_reverse_iterator rend() const   { return const_reverse_iterator(this->begin()); }

  // CAPACITY

  // Test whether container is empty
  bool empty() const { return _tree.empty(); }

  // Return container size
  size_type size() const { return _tree.get_size(); };

  // Return maximum size
  size_type max_size() const { return _tree.get_node_allocator().max_size(); }

  // Element access

  // Access element
  mapped_type &operator[](const key_type &k) {
    return _tree.find_or_insert(k);
  }


  // MODIFIERS

  // Insert elements
  pair<iterator, bool> insert(const value_type &val) {
    pair<bst_node_type *, bool> insertResult = _tree.insert(val);
    return make_pair(iterator(insertResult.first), insertResult.second);
  }

  iterator insert(iterator position, const value_type &val) {
    (void)position;
    pair<bst_node_type *, bool> insertResult = _tree->insert(val);
    return iterator(insertResult.first);
  }

  template <class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    for (InputIterator it = first; it != last; ++it) {
      insert(*it);
    }
  }

  // Erase elements
  void erase(iterator position) {
    key_type const &k = position->first;
    _tree.remove(k);
  }

  size_type erase(const key_type &k) {
    return _tree.remove(k);
  }

  void erase(iterator first, iterator last) {
    iterator current;
    while (first != last) {
      iterator current = first++;
      this->erase(current);
    }
  }

  // Swap content
  void swap(map &x) {
    _tree.swap(x._tree);
  }

  // Clear content
  void clear() {
    _tree.clear();
  }


  // OBSERVERS

  // Return key comparison object
  key_compare key_comp() const { return _key_comp; }
  // Return value comparison object
  value_compare value_comp() const { return _comp; }


  // OPERATIONS

  // Get iterator to element
  iterator find(const key_type &k) {
    bst_node_type *n = _tree.find(k);
    return iterator(n);
  }

  const_iterator find(const key_type &k) const {
    bst_node_type const *n = _tree.find(k);
    return const_iterator(n);
  }

  // Count elements with a specific key
  size_type count(const key_type &k) const {
    return this->find(k) == this->end() ? 0 : 1;
  };

  // Return iterator to lower bound
  iterator lower_bound(const key_type &k)
    { return iterator(_tree.lower_bound(k)); }
  const_iterator lower_bound(const key_type &k) const
    { return const_iterator(_tree.lower_bound(k)); }

  // Return iterator to upper bound
  iterator upper_bound(const key_type &k)
    { return iterator(_tree.upper_bound(k)); }
  const_iterator upper_bound(const key_type &k) const
    { return const_iterator(_tree.upper_bound(k)); }

  // Get range of equal elements
  pair<const_iterator, const_iterator> equal_range(const key_type &k) const
    { return pair<const_iterator, const_iterator>(_tree.equal_range(k)); }
  pair<iterator, iterator> equal_range(const key_type &k)
    { return pair<iterator, iterator>(_tree.equal_range(k)); }


  // ALLOCATOR

  // Get allocator
  allocator_type get_allocator() const
    { return _tree.get_value_allocator(); }


 private:
  bst_type       _tree;
  key_compare    _key_comp;
  value_compare  _comp;
  allocator_type _alloc;
};

template <class KeyType,
          class MappedType,
          class KeyCompare,
          class ValueAlloc>
struct map<KeyType, MappedType, KeyCompare, ValueAlloc>::value_compare {
  typedef bool result_type;
  typedef key_type first_argument_type;
  typedef mapped_type second_argument_type;

  value_compare(KeyCompare c) : kComp(c) {}
  bool operator()(const value_type &x, const value_type &y) const {
    return kComp(x.first, y.first);
  }

  KeyCompare kComp;
};

template <class KeyType,
          class MappedType,
          class KeyCompare,
          class ValueAlloc>
template  <class ValueType,
          class NodeType>
class map<KeyType, MappedType, KeyCompare, ValueAlloc>::Iterator {
 public:
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef std::ptrdiff_t                  difference_type;
  typedef ValueType                       value_type;
  typedef ValueAlloc                      allocator_type;
  typedef ValueType                       *pointer;
  typedef ValueType                       &reference;
  typedef NodeType                        node_type;

  Iterator() : _tree_ptr(NULL), _current_node(NULL), _is_end(true) {}

  Iterator(map const &map, bool isEnd) : _tree_ptr(&map._tree), _is_end(isEnd) {
    if (_tree_ptr->_root == NULL || isEnd) {
      _is_end = true;
      _current_node = NULL;
    } else
      _current_node = _tree_ptr->_root->leftmost_child();
  }

  Iterator(node_type *node)
      : _tree_ptr(node == NULL ? NULL : &node->_tree),
        _current_node(node),
        _is_end(node == NULL) {}

  Iterator(Iterator const &x): _tree_ptr(x._tree_ptr), _current_node(x._current_node), _is_end(x._is_end) {}

  Iterator &operator=(Iterator const &x) {
    _tree_ptr = x._tree_ptr;
    _current_node = x._current_node;
    _is_end = x._is_end;
    return *this;
  }

  reference operator*() const { return *_current_node->get_value(); }
  pointer operator->() const { return _current_node->get_value(); }

  Iterator &operator++() {
    node_type *n = _current_node->next();
    if (n != NULL)
      _current_node = n;
    else {
      _is_end = true;
      _current_node = NULL;
    }
    return *this;
  }
  Iterator operator++(int) {
    Iterator old_value(*this);
    operator++();
    return old_value;
  }

  Iterator &operator--() {
    if (_is_end) {
      _is_end = false;
      _current_node = _tree_ptr->_root->rightmost_child();
    } else
      _current_node = _current_node->previous();
    return *this;
  }
  Iterator operator--(int) {
    Iterator old_value(*this);
    this->operator--();
    return old_value;
  }

  friend bool operator==(Iterator const &a, Iterator const &b) {
    if ((a._tree_ptr == NULL && b._is_end) || (a._is_end && b._tree_ptr == NULL))
      return true;
    if (a._is_end && b._is_end)
      return true;
    if (a._is_end != b._is_end)
      return false;
    return a._current_node == b._current_node;
  }
  friend bool operator!=(Iterator const &a, Iterator const &b) {
    return !(a == b);
  }

 private:
  bst_type const *_tree_ptr;
  node_type      *_current_node;
  bool           _is_end;
};

template <class KeyType,
          class MappedType,
          class KeyCompare,
          class ValueAlloc>
class map<KeyType, MappedType, KeyCompare, ValueAlloc>::BST {
 public:
  struct Node;

  typedef KeyType key_type;
  typedef MappedType mapped_type;
  typedef pair<const key_type, mapped_type> value_type;
  typedef KeyCompare key_compare;
  typedef typename map::value_compare value_compare;
  typedef ValueAlloc value_allocator_type;
  typedef typename ValueAlloc::template rebind<Node>::other node_allocator_type;

  friend class map;

  // Constructors

  BST(const key_compare &kComp = key_compare(),
      allocator_type const &vAlloc = value_allocator_type())
      : _root(NULL), _key_comp(kComp), _value_comp(kComp), _value_alloc(vAlloc),
        _node_alloc(vAlloc), _a_node_was_removed(false) {}

  BST(BST const &x)
      : _root(NULL), _key_comp(x._key_comp), _value_comp(x._key_comp), _value_alloc(x._value_alloc),
        _node_alloc(x._value_alloc), _a_node_was_removed(x._a_node_was_removed) {
    _root = Node::deepcopy(x._root, NULL);
  }

  // Destructor

  ~BST() {
    this->clear();
    _root = NULL;
  }

  BST &operator=(BST const &x) {
    this->clear();
    _root = Node::deepcopy(x._root, NULL);
    return *this;
  }

  // CAPACITY

  size_t get_size() const {
    return Node::get_size(_root);
  }

  bool empty() {
    return _root == NULL;
  }


  // MODIFIERS

  pair<Node *, bool> insert(value_type const &new_val) {
    _root = Node::insert(_root, new_val, *this);
    Node *lastAdded = _root->get_last_added();
    bool oneWasAdded = _root->get_one_was_added();
    return make_pair<Node *, bool>(lastAdded, oneWasAdded);
  }

  size_type remove(key_type const &kVal) {
    _root = Node::remove(_root, kVal, *this);
    if (_root != NULL)
      _root->update_height();
    return _a_node_was_removed ? 1 : 0;
  }

  void clear() {
    Node::clear(_root);
    _root = NULL;
  }

  void swap(BST &x) {
    std::swap(_root, x._root);
  }


  // OPERATIONS

  Node *find(key_type const &kVal) {
    return Node::find(_root, kVal);
  }
  Node const *find(key_type const &kVal) const {
    return Node::find(_root, kVal);
  }

  mapped_type &find_or_insert(key_type const &kVal) {
    Node *n = Node::find(_root, kVal);
    if (n != NULL)
      return n->_value->second;
    else {
      this->insert(make_pair(kVal, mapped_type()));
      return _root->get_last_added()->_value->second;
    }
  }

  Node *lower_bound(key_type const &kVal) const {
    return Node::lower_bound(_root, kVal);
  }

  Node *upper_bound(key_type const &kVal) const {
    return Node::upper_bound(_root, kVal);
  }

  pair<Node const *, Node const *> equal_range(key_type const &k) const {
    Node const *n = this->lower_bound(k);
    if (n->get_value()->first == k)
      return make_pair(n, n->next());
    else
      return make_pair(n, n);
  }
  pair<Node *, Node *> equal_range(key_type const &k) {
    pair<Node const *, Node const *> equal_range_const = \
      const_cast<BST const *>(this)->equal_range(k);
    return make_pair(const_cast<Node *>(equal_range_const.first),
                     const_cast<Node *>(equal_range_const.second));
  }

  friend bool operator==(BST const &a, BST const &b) { return a._root == b._root; }
  friend bool operator!=(BST const &a, BST const &b) { return a._root != b._root; }

  value_allocator_type get_value_allocator() const { return _value_alloc; };
  node_allocator_type get_node_allocator() const { return _node_alloc; };
  value_compare get_key_comparator() const { return _key_comp; };
  value_compare get_value_comparator() const { return _value_comp; };

 private:

  // MEMORY

  value_type *new_value(value_type const &val) {
    value_type *val_addr = _value_alloc.allocate(1);
    _value_alloc.construct(val_addr, val);
    return val_addr;
  }

  void delete_value(value_type *val_addr) {
    if (val_addr == NULL)
      return;
    _value_alloc.destroy(val_addr);
    _value_alloc.deallocate(val_addr, 1);
  }

  Node *new_node(value_type const &val) {
    Node *n = _node_alloc.allocate(1);
    _node_alloc.construct(n, val, *this);
    return n;
  }

  void delete_node(Node *n) {
    if (n == NULL)
      return;
    _node_alloc.destroy(n);
    _node_alloc.deallocate(n, 1);
  }

  Node                 *_root;
  key_compare          _key_comp;
  value_compare        _value_comp;
  value_allocator_type _value_alloc;
  node_allocator_type  _node_alloc;
  bool                 _a_node_was_removed;
};

template <class KeyType,
          class MappedType,
          class KeyCompare,
          class ValueAlloc>
struct map<KeyType, MappedType, KeyCompare, ValueAlloc>::BST::Node {

  // Constructor

  Node(value_type const &val, BST &bst)
      : _tree(bst), _value(NULL), _left(NULL), _right(NULL), _parent(NULL),
        _height(1), _a_node_was_added(true) {
    _value = _tree.new_value(val);
    _last_node_added = this;
  }

  // Destructor

  ~Node() {
    _tree.delete_value(_value);
  }

  // Assignment

    Node &operator=(Node const &x) {
    _value = x._value;
    _left = x._left;
    _right = x._right;
    _parent = x._parent;
    _height = x._height;
    _a_node_was_added = x._a_node_was_added;
    return *this;
  }

  // BALANCING

  static void set_parent(Node *n, Node *p) {
    if (n != NULL)
      n->_parent = p;
  }

  static Node *rotate_left(Node *x) {
    Node *xOldParent = x->_parent;
    Node *y = x->_right;
    Node *yL = y->_left;

    x->_right = yL;
    set_parent(yL, x);
    y->_left = x;
    set_parent(x, y);

    x->update_height();
    y->update_height();
    set_parent(y, xOldParent);
    return y;
  }

  static Node *rotate_right(Node *y) {
    Node *yOldParent = y->_parent;
    Node *x = y->_left;
    Node *xR = x->_right;

    y->_left = xR;
    set_parent(xR, y);
    x->_right = y;
    set_parent(y, x);

    y->update_height();
    x->update_height();
    set_parent(x, yOldParent);
    return x;
  }

  static Node *rebalance_cases(Node *p, bool isLeft1, bool isLeft2) {
    // Left Left Case
    if (isLeft1 && isLeft2) {
      return rotate_right(p);
    }
    // Left Right Case
    else if (isLeft1 && !isLeft2) {
      p->_left = rotate_left(p->_left);
      Node::set_parent(p->_left, p);
      return rotate_right(p);
    }
    // Right Left Case
    else if (!isLeft1 && isLeft2) {
      p->_right = rotate_right(p->_right);
      Node::set_parent(p->_right, p);
      return rotate_left(p);
    }
    // Right Right Case
    else {
      return rotate_left(p);
    }
  }


  // INSERTION

  static Node *rebalance_after_insert(Node *p, value_type const &new_val) {
    int balance = p->get_balance();
    if (balance >= -1 && balance <= 1)
      return p;
    Node *child = balance > 1 ? p->_left : p->_right;
    return Node::rebalance_cases(p, balance > 1, new_val < *child);
  }

  // Insert new_val in p
  // return the new root where p were (possibly p itself)
  static Node *insert(Node *p, value_type const &new_val, BST &bst) {
    if (p == NULL) {
      return bst.new_node(new_val);
    }
    Node *p_son;
    if (new_val < *p) {
      p->_left = Node::insert(p->_left, new_val, bst);
      p_son = p->_left;
    } else if (*p < new_val) {
      p->_right = Node::insert(p->_right, new_val, bst);
      p_son = p->_right;
    } else {
      p->_last_node_added = p;
      p->_a_node_was_added = false;
      return p;
    }
    p_son->_parent = p;
    p->_last_node_added = p_son->_last_node_added;
    p->_a_node_was_added = p_son->_a_node_was_added;
    p->update_height();
    return Node::rebalance_after_insert(p, new_val);
  }


  // DELETION UTILS

  static void change_between_n1_n2(Node **n, Node *n1, Node *n2) {
    if (*n == n1)
      *n = n2;
    else if (*n == n2)
      *n = n1;
  }
  static void switch_n1_n2_addresses_in_n(Node *n, Node *n1, Node *n2) {
    if (n == NULL)
      return;
    Node::change_between_n1_n2(&n->_left, n1, n2);
    Node::change_between_n1_n2(&n->_right, n1, n2);
    Node::change_between_n1_n2(&n->_parent, n1, n2);
  }
  static size_t add_uniquely(Node *(&array)[8], size_t len, Node *n) {
    for (size_t i = 0; i < len; ++i) {
      if (array[i] == n)
        return len;
    }
    array[len] = n;
    return len + 1;
  }
  static size_t add_direct_neighbors_of(Node *(&array)[8], size_t len, Node *n) {
    len = add_uniquely(array, len, n->_left);
    len = add_uniquely(array, len, n->_right);
    len = add_uniquely(array, len, n->_parent);
    return len;
  }
  static size_t add_neighborhood_of_n1_n2(Node *(&neighborhood)[8], Node *n1, Node *n2) {
    size_t len;
    len = add_direct_neighbors_of(neighborhood, 0, n1);
    len = add_direct_neighbors_of(neighborhood, len, n2);
    len = add_uniquely(neighborhood, len, n1);
    len = add_uniquely(neighborhood, len, n2);
    return len;
  }
  static void switch_n1_n2_addresses_for_neighborhood(Node *n1, Node *n2) {
    Node *neighborhood[8];
    size_t len = Node::add_neighborhood_of_n1_n2(neighborhood, n1, n2);
    for (size_t i = 0; i < len; ++i) {
      Node::switch_n1_n2_addresses_in_n(neighborhood[i], n1, n2);
    }
  }
  static void swap_n1_n2_positional_members(Node *n1, Node *n2) {
    std::swap(n1->_parent, n2->_parent);
    std::swap(n1->_left, n2->_left);
    std::swap(n1->_right, n2->_right);
    std::swap(n1->_height, n2->_height);
    std::swap(n1->_a_node_was_added, n2->_a_node_was_added);
  }
  // Swap two nodes in the tree, preserving the couples (address, _value)
  static void swap_nodes(Node *n1, Node *n2) {
    Node::switch_n1_n2_addresses_for_neighborhood(n1, n2);
    Node::swap_n1_n2_positional_members(n1, n2);
  }

  static Node *delete_and_move_only_child_up(Node *p, BST &bst) {
    Node *child = (p->_left != NULL) ? p->_left : p->_right;
    child->_parent = p->_parent;
    if (child->_parent != NULL)
      child->_parent->update_height();
    bst.delete_node(p);
    bst._a_node_was_removed = true;
    return child;
  }

  static Node *delete_leaf(Node *leaf, BST &bst) {
    bst.delete_node(leaf);
    bst._a_node_was_removed = true;
    return NULL;
  }

  static Node *rebalance_after_remove(Node *p) {
    int balance[2];
    balance[0] = p->get_balance();
    if (balance[0] >= -1 && balance[0] <= 1)
      return p;
    balance[1] = balance[0] > 1 ? p->_left->get_balance() : p->_right->get_balance();
    return Node::rebalance_cases(p, balance[0] > 0, balance[1] > 0);
  }

  static Node *swap_with_next_node(Node *p) {
    Node *k = p->next();
    Node::swap_nodes(p, k);
    return k;
  }


  // DELETION

  static Node *remove(Node *p, key_type const &kVal, BST &bst) {
    if (p == NULL) {
      bst._a_node_was_removed = false;
      return NULL;
    }
    if (kVal < *p)
      p->_left = Node::remove(p->_left, kVal, bst);
    else if (*p < kVal)
      p->_right = Node::remove(p->_right, kVal, bst);
    else {
      if (p->_left == NULL && p->_right == NULL)
        return Node::delete_leaf(p, bst);
      else if (p->_left == NULL || p->_right == NULL)
        return Node::delete_and_move_only_child_up(p, bst);
      else {
        p = Node::swap_with_next_node(p);
        p->_right = Node::remove(p->_right, kVal, bst);
      }
    }
    p->update_height();
    return Node::rebalance_after_remove(p);
  }


  // FIND AND RANGES

  static Node const *find(Node const *p, key_type const &kVal) {
    if (p == NULL)
      return NULL;
    if (kVal < *p) {
      return Node::find(p->_left, kVal);
    } else if (kVal > *p) {
      return Node::find(p->_right, kVal);
    } else {
      return p;
    }
  }
  static Node *find(Node *p, key_type const &kVal)
    { return const_cast<Node *>(find(const_cast<const Node *>(p), kVal)); }

  static Node *lower_bound(Node *p, key_type const &kVal) {
    if (p == NULL)
      return NULL;
    if (kVal < *p) {
      if (p->_left == NULL)
        return p;
      else
        return lower_bound(p->_left, kVal);
    } else if (kVal > *p) {
      if (p->_right == NULL)
        return p->next();
      else
        return lower_bound(p->_right, kVal);
    } else
      return p;
  }

  static Node *upper_bound(Node *p, key_type const &kVal) {
    if (p == NULL)
      return NULL;
    if (kVal < *p) {
      if (p->_left == NULL)
        return p;
      else
        return upper_bound(p->_left, kVal);
    } else if (kVal > *p) {
      if (p->_right == NULL)
        return p->next();
      else
        return upper_bound(p->_right, kVal);
    } else
      return p->next();
  }


  // SIZE

  static size_t get_size(Node const *p) {
    if (p == NULL)
      return (0);
    return (1 + Node::get_size(p->_left) + Node::get_size(p->_right));
  }


  // HEIGHT

  static int node_height(Node *n) { return n == NULL ? 0 : n->_height; }


  // CLEAR

  static void clear(Node *p) {
    if (p == NULL)
      return;
    clear(p->_left);
    clear(p->_right);
    p->_tree.delete_node(p);
  }


  // COPY

  static Node *deepcopy(Node const *p, Node *pCopyParent) {
    if (p == NULL)
      return (NULL);
    Node *pCopy = new Node(*p->_value, p->_tree);
    pCopy->_parent = pCopyParent;
    pCopy->_height = p->_height;
    pCopy->_left = deepcopy(p->_left, pCopy);
    pCopy->_right = deepcopy(p->_right, pCopy);
    return pCopy;
  }


  // NAVIGATION

  Node const *leftmost_child() const {
    if (_left == NULL)
      return this;
    return _left->leftmost_child();
  }
  Node *leftmost_child()
    { return const_cast<Node *>(const_cast<const Node *>(this)->leftmost_child()); }

  Node const *rightmost_child() const {
    if (_right == NULL)
      return this;
    return _right->rightmost_child();
  }
  Node *rightmost_child()
    { return const_cast<Node *>(const_cast<const Node *>(this)->rightmost_child()); }

  bool is_left_child() const
    { return _parent != NULL && _parent->_left == this; }

  bool is_right_child() const
    { return _parent != NULL && _parent->_right == this; }

  Node const *first_parent_left() const {
    if (_parent == NULL)
      return NULL;
    if (this->is_left_child())
      return _parent;
    return _parent->first_parent_left();
  }
  Node *first_parent_left()
    { return const_cast<Node *>(const_cast<const Node *>(this)->first_parent_left()); }

  Node const *first_parent_right() const {
    if (_parent == NULL)
      return NULL;
    if (this->is_right_child())
      return _parent;
    return _parent->first_parent_right();
  }
  Node *first_parent_right()
    { return const_cast<Node *>(const_cast<const Node *>(this)->first_parent_right()); }

  Node *get_root() {
    if (_parent == NULL)
      return this;
    return _parent->get_root();
  }

  Node const *next() const {
    if (_right != NULL)
      return _right->leftmost_child();
    return this->first_parent_left();
  }
  Node *next()
    { return const_cast<Node *>(const_cast<const Node *>(this)->next()); }

  Node const *previous() const {
    if (_left != NULL)
      return _left->rightmost_child();
    return this->first_parent_right();
  }
  Node *previous()
    { return const_cast<Node *>(const_cast<const Node *>(this)->previous()); }


  // UPDATE HEIGHT

  void update_height()
    { _height = 1 + std::max(node_height(_left), node_height(_right)); }


  // GETTERS

  int get_balance()
    { return node_height(_left) - node_height(_right); }
  Node *get_last_added()
    { return _last_node_added; }
  bool get_one_was_added()
    { return _a_node_was_added; }
  value_type const *get_value() const
    { return _value; }
  value_type *get_value()
    { return _value; }


  // RELATIONAL OPERATORS

  friend bool operator<(Node const &a, value_type const &b) { return a._tree._value_comp(*a._value, b); }
  friend bool operator<(Node const &a, key_type const &b)   { return a._tree._key_comp(a._value->first, b); }
  friend bool operator<(value_type const &a, Node const &b) { return b._tree._value_comp(a, *b._value); }
  friend bool operator<(key_type const &a, Node const &b)   { return b._tree._key_comp(a, b._value->first); }
  friend bool operator>(Node const &a, value_type const &b) { return a._tree._value_comp(b, *a._value); }
  friend bool operator>(Node const &a, key_type const &b)   { return a._tree._key_comp(b, a._value->first); }
  friend bool operator>(value_type const &a, Node const &b) { return b._tree._value_comp(*b._value, a); }
  friend bool operator>(key_type const &a, Node const &b)   { return b._tree._key_comp(b._value->first, a); }

  BST        &_tree;
  value_type *_value;
  Node       *_left;
  Node       *_right;
  Node       *_parent;
  int        _height;
  Node       *_last_node_added;
  bool       _a_node_was_added;
};

}  // namespace ft
