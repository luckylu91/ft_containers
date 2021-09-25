#pragma once
#include <memory>
#include <functional>
// #include <cmath>
#include <algorithm> // max
#include "pair.hpp"
// //
// #include <iostream>
// #include <iomanip>


namespace ft {

template <class Key,
          class T,
          class KeyCompare = std::less<Key>,
          class Alloc = std::allocator<pair<const Key,T> > >
class map {
 public:
  class BST;
  template<class IteratorType> class Iterator;
  class value_compare;

  typedef Key                                      key_type;
  typedef T                                        mapped_type;
  typedef pair<const key_type,mapped_type>         value_type;
  typedef KeyCompare                               key_compare;
  typedef Alloc                                    allocator_type;
  typedef typename allocator_type::reference       reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer         pointer;
  typedef typename allocator_type::const_pointer   const_pointer;
  typedef Iterator<value_type>                     iterator;
  typedef Iterator<const value_type>               const_iterator;
  typedef std::reverse_iterator<iterator>          reverse_iterator;
  typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;
  typedef typename allocator_type::difference_type difference_type;
  typedef typename allocator_type::size_type       size_type;

  typedef BST                bst_type;
  typedef typename BST::Node bst_node_type;

// Construct map (public member function )
  // empty (1)
  explicit map(const key_compare& kComp = key_compare(),
               const allocator_type& alloc = allocator_type()) : _tree(kComp, alloc), _kComp(kComp), _comp(kComp), _alloc(alloc) {}

  // range (2)
  template <class InputIterator>
    map(InputIterator first, InputIterator last,
         const key_compare& kComp = key_compare(),
         const allocator_type& alloc = allocator_type()) : _tree(kComp, alloc), _kComp(kComp), _comp(kComp), _alloc(alloc) {
      for (InputIterator it = first; it != last; ++it)
        this->insert(*it);
    }

  // copy (3)
  map(const map& x)
    : _tree(x._tree), _kComp(x._kComp),
      _comp(x._comp), _alloc(x._alloc) {}

// Map destructor (public member function )
  ~map() {}

// Copy container content (public member function )
  map& operator= (const map& x) {
    this->_tree = x._tree;
    return *this;
  }

// Iterators

  // Return iterator to beginning (public member function )
  iterator begin()                      { return iterator(*this, false); }
  const_iterator begin() const          { return const_iterator(*this, false); }
  // Return iterator to end (public member function )
  iterator end()                        { return iterator(*this, true); }
  const_iterator end() const            { return const_iterator(*this, true); }
  // Return reverse iterator to reverse beginning (public member function )
  reverse_iterator rbegin()             { return reverse_iterator(this->end()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }
  // Return reverse iterator to reverse end (public member function )
  reverse_iterator rend()               { return reverse_iterator(this->begin()); }
  const_reverse_iterator rend() const   { return const_reverse_iterator(this->begin()); }

// Capacity

  // Test whether container is empty (public member function )
  bool empty() const { return this->_tree.empty(); }

  // Return container size (public member function )
  size_type size() const { return this->_tree.get_size(); };

  // Return maximum size (public member function )
  size_type max_size() const { return this->_alloc.max_size(); }

// Element access

  // Access element (public member function )
  mapped_type& operator[] (const key_type& k) {
    return this->_tree.find_or_insert(k);
  }

// Modifiers

  // Insert elements (public member function )
  pair<iterator,bool> insert (const value_type& val) {
    pair<bst_node_type*, bool> insertResult = this->_tree.insert(val);
    return make_pair(iterator(*this, insertResult.first), insertResult.second);
  }

  // MEILLEUR MOYEN ?
  iterator insert(iterator position, const value_type& val) {
    (void)position;
    pair<bst_node_type*, bool> insertResult = this->_tree->insert(val);
    return iterator(*this, insertResult.first);
  }

  template <class InputIterator>  void insert(InputIterator first, InputIterator last) {
    for (InputIterator it = first; it != last; ++it) {
      insert(*it);
    }
  }

  // Erase elements (public member function )
  void erase (iterator position) {
    key_type &k = position->first;
    this->_tree.remove(k);
  }

  size_type erase (const key_type& k) {
    return this->_tree.remove(k);
  }

  void erase (iterator first, iterator last) {
    for (iterator it = first; it != last; ++it) {
      this->erase(it);
    }
  }

  // Swap content (public member function )
  void swap (map &x) {
    this->_tree.swap(x._tree);
  }

  // Clear content (public member function )
  void clear() {
    this->_tree.clear();
  }

// Observers

  // Return key comparison object (public member function )
  key_compare key_comp() const { return this->_kComp; }
  // Return value comparison object (public member function )
  value_compare value_comp() const { return this->_comp; }

// Operations

  // Get iterator to element (public member function )
  iterator find (const key_type& k) {
    bst_node_type *n = this->_tree->find(k);
    return iterator(*this, n);
  }

  const_iterator find (const key_type& k) const {
    bst_node_type *n = this->_tree->find(k);
    return const_iterator(*this, n);
  }

  // Count elements with a specific key (public member function )
  size_type count (const key_type& k) const {
    return this->find(k) == this->end() ? 0 : 1;
  };

  // Return iterator to lower bound (public member function )
  iterator lower_bound (const key_type& k)             { return iterator(this->_tree->lower_bound(k)); }
  const_iterator lower_bound (const key_type& k) const { return const_iterator(this->_tree->lower_bound(k)); }

  // Return iterator to upper bound (public member function )
  iterator upper_bound (const key_type& k)             { return iterator(this->_tree->upper_bound(k)); }
  const_iterator upper_bound (const key_type& k) const { return const_iterator(this->_tree->upper_bound(k)); }

  // Get range of equal elements (public member function )
  pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
    return pair<const_iterator, const_iterator>(this->_tree->equal_range(k));
  }
  pair<iterator,iterator>             equal_range (const key_type& k) {
    return pair<iterator, iterator>(this->_tree->equal_range(k));
  }

// Allocator

  // Get allocator (public member function )
  allocator_type get_allocator() const { return this->_tree.get_allocator(); }

  template <class IteratorType>
    class Iterator {
   public:
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    typedef IteratorType value_type;
    typedef Alloc allocator_type;
    typedef IteratorType* pointer;
    typedef IteratorType& reference;

    Iterator(map const & map, bool isEnd) : bst(map._tree), isEnd(isEnd) {
      if (this->bst.root == NULL || isEnd) {
        this->isEnd = true;
        this->current = NULL;
      }
      else
        this->current = this->bst.root->leftmost_child();
    }

    Iterator(map const & map, bst_node_type *node) : bst(map._tree), isEnd(node != NULL) {
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
      bst_node_type *n = this->current->next();
      if (n != NULL)
        this->current = n;
      else
        this->isEnd = true;
      return *this;
    }
    Iterator operator++(int) {
      Iterator old_value(*this);
      this->operator++();
      return old_value;
    }
    Iterator &operator--() {
      if (this->isEnd) {
        this->isEnd = false;
        if (this->current == NULL)
          this->current = this->bst.root->rightmost_child();
      }
      else
        this->current = this->current->previous();
      return *this;
    }
    Iterator operator--(int) {
      Iterator old_value(*this);
      this->operator--();
      return old_value;
    }
    friend bool operator==(Iterator const &a, Iterator const &b) {
      return a.bst == b.bst && a.isEnd == b.isEnd && (a.isEnd || (!a.isEnd && a.current == b.current));
    }
    friend bool operator!=(Iterator const &a, Iterator const &b) {
      return a.bst != b.bst || a.isEnd != b.isEnd || (!a.isEnd && a.current != b.current);
    }

   private:
    bst_node_type *current;
    bst_type const & bst;
    bool isEnd;
  };

 private:
  bst_type _tree;
  key_compare _kComp;
  value_compare _comp;
  allocator_type _alloc;
};

template <class KeyType, class MappedType, class KeyCompare, class Alloc>
class map<KeyType, MappedType, KeyCompare, Alloc>::value_compare
{
public:
  KeyCompare kComp;
  value_compare (KeyCompare c) : kComp(c) {}
  typedef bool result_type;
  typedef key_type first_argument_type;
  typedef mapped_type second_argument_type;
  bool operator() (const value_type& x, const value_type& y) const {
    return kComp(x.first, y.first);
  }
};

template <class KeyType, class MappedType, class KeyCompare, class Alloc>
class map<KeyType, MappedType, KeyCompare, Alloc>::BST {
 public:
  typedef KeyType key_type;
  typedef MappedType mapped_type;
  typedef pair<const key_type, mapped_type> value_type;
  typedef KeyCompare key_compare;
  // typedef ValueCompare value_compare;
  typedef typename map::value_compare value_compare;
  typedef Alloc allocator_type;

  friend class map;

  struct Node {
    Node(value_type const & val, value_compare & comp, allocator_type & alloc)
      : value(NULL), left(NULL), right(NULL), parent(NULL), height(1), kComp(comp.kComp), comp(comp), alloc(alloc), oneWasAdded(true) {
        this->value = this->alloc.allocate(1);
        this->alloc.construct(this->value, val);
        lastAdded = this;
    }

    ~Node() {
      alloc.destroy(this->value);
      alloc.deallocate(this->value, 1);
    }

    static void set_parent(Node *n, Node *p) {
      if (n != NULL)
        n->parent = p;
    }

    static void permute(Node *a, Node *b) {
      std::swap(*a, *b);
      std::swap(a->value, b->value);
    }

    static Node *rotate_left(Node *x) {
      Node *xOldParent = x->parent;
      Node *y = x->right;
      Node *yL = y->left;

      x->right = yL;
      set_parent(yL, x);
      y->left = x;
      set_parent(x, y);

      x->update_height();
      y->update_height();
      set_parent(y, xOldParent);
      return y;
    }

    static Node *rotate_right(Node *y) {
      Node *yOldParent = y->parent;
      Node *x = y->left;
      Node *xR = x->right;

      y->left = xR;
      set_parent(xR, y);
      x->right = y;
      set_parent(y, x);

      y->update_height();
      x->update_height();
      set_parent(x, yOldParent);
      return x;
    }

    static Node *do_rebalance_cases(Node *p, bool isLeft1, bool isLeft2) {
      // Left Left Case
      if (isLeft1 && isLeft2) {
        return rotate_right(p);
      }
      // Left Right Case
      else if (isLeft1 && !isLeft2) {
        p->left = rotate_left(p->left);
        Node::set_parent(p->left, p);
        return rotate_right(p);
      }
      // Right Left Case
      else if (!isLeft1 && isLeft2) {
        p->right = rotate_right(p->right);
        Node::set_parent(p->right, p);
        return rotate_left(p);
      }
      // Right Right Case
      else {
        return rotate_left(p);
      }
    }

    // returns the new root in stead of "p"
    static Node *insert(Node *p, value_type const &new_val, BST &bst) {
      if (p == NULL) {
        return new Node(new_val, bst.comp, bst.alloc);
      }
      if (new_val < *p) {
        p->left = Node::insert(p->left, new_val, bst);
        p->left->parent = p;
        p->lastAdded = p->left->lastAdded;
        p->oneWasAdded = p->left->oneWasAdded;
      }
      else if (*p < new_val) {
        p->right = Node::insert(p->right, new_val, bst);
        p->right->parent = p;
        p->lastAdded = p->right->lastAdded;
        p->oneWasAdded = p->right->oneWasAdded;
      }
      else {
        p->lastAdded = p;
        p->oneWasAdded = false;
        return p;
      }
      p->update_height();
      int balance = p->get_balance();
      if (balance >= -1 && balance <= 1)
        return p;
      Node *child = balance > 1 ? p->left : p->right;
      return Node::do_rebalance_cases(p, balance > 1, new_val < *child);
    }

    static Node *move_only_child_up(Node *p) {
      Node *temp = p->left != NULL ? p->left : p->right;
      temp->parent = p->parent;
      p->left = NULL;
      p->right = NULL;
      delete p;
      return temp;
    }

    // TODO balance
    static Node *remove(Node *p, key_type const &kVal, BST &bst) {
      if (p == NULL) {
        bst.oneWasRemoved = false;
        return NULL;
      }
      if (kVal < *p) {
        p->left = Node::remove(p->left, kVal, bst);
      }
      else if (*p < kVal) {
        p->right = Node::remove(p->right, kVal, bst);
      }
      else {
        if (p->left == NULL && p->right == NULL) {
          delete p;
          bst.oneWasRemoved = true;
          return NULL;
        }
        else if (p->left == NULL || p->right == NULL) {
          bst.oneWasRemoved = true;
          return Node::move_only_child_up(p);
        }
        else {
          Node *k = p->next();
          std::swap(p->value, k->value);
          p->right = Node::remove(p->right, kVal, bst);
        }
      }
      p->update_height();
      int balance[2];
      balance[0] = p->get_balance();
      if (balance[0] >= -1 && balance[0] <= 1)
        return p;
      balance[1] = balance[0] > 1 ? p->left->get_balance() : p->right->get_balance();
      return Node::do_rebalance_cases(p, balance[0] > 0, balance[1] > 0);
    }

    static Node *find(Node *p, key_type const & kVal) {
      if (p == NULL)
        return NULL;
      if (kVal < *p) {
        return Node::find(p->left, kVal);
      }
      else if (kVal > *p) {
        return Node::find(p->right, kVal);
      }
      else {
        return p;
      }
    }

    static Node *lower_bound(Node const *p, key_type const & kVal) {
      if (p == NULL)
        return NULL;
      if (kVal < *p) {
        if (p->left == NULL)
          return p;
        else
          return lower_bound(p->left, kVal);
      }
      else if (*kVal > *p) {
        if (p->right == NULL)
          return p->next();
        else
          return lower_bound(p->right, kVal);
      }
      else
        return p;
    }

    static Node *upper_bound(Node const *p, key_type const & kVal) {
      if (p == NULL)
        return NULL;
      if (kVal < *p) {
        if (p->left == NULL)
          return p;
        else
          return upper_bound(p->left, kVal);
      }
      else if (*kVal > *p) {
        if (p->right == NULL)
          return p->next();
        else
          return upper_bound(p->right, kVal);
      }
      else
        return p->next();
    }

    static size_t get_size(Node const *p) {
      if (p == NULL)
        return (0);
      return (1 + Node::get_size(p->left) + Node::get_size(p->right));
    }

    Node const *leftmost_child() const {
      if (this->left == NULL)
        return this;
      return this->left->leftmost_child();
    }
    Node *leftmost_child() {
      return const_cast<Node*>(const_cast<const Node*>(this)->leftmost_child());
    }

    Node const *rightmost_child() const {
      if (this->right == NULL)
        return this;
      return this->right->rightmost_child();
    }
    Node *rightmost_child() {
      return const_cast<Node*>(const_cast<const Node*>(this)->rightmost_child());
    }

    bool is_left_child() const {
      return this->parent != NULL && this->parent->left == this;
    }

    bool is_right_child() const {
      return this->parent != NULL && this->parent->right == this;
    }

    Node const *first_parent_left() const {
      if (this->parent == NULL)
        return NULL;
      if (this->is_left_child())
        return this->parent;
      return this->parent->first_parent_left();
    }
    Node *first_parent_left() {
      return const_cast<Node*>(const_cast<const Node*>(this)->first_parent_left());
    }

    Node const *first_parent_right() const {
      if (this->parent == NULL)
        return NULL;
      if (this->is_right_child())
        return this->parent;
      return this->parent->first_parent_right();
    }
    Node *first_parent_right() {
      return const_cast<Node*>(const_cast<const Node*>(this)->first_parent_right());
    }

    Node *get_root() const {
      if (this->parent == NULL)
        return this;
      return this->parent->get_root();
    }

    Node const *next() const {
      if (this->right != NULL)
        return this->right->leftmost_child();
      return this->first_parent_left();
    }
    Node *next() {
      return const_cast<Node*>(const_cast<const Node*>(this)->next());
    }

    Node const *previous() const {
      if (this->left != NULL)
        return this->left->rightmost_child();
      return this->first_parent_right();
    }
    Node *previous() {
      return const_cast<Node*>(const_cast<const Node*>(this)->previous());
    }

    static int node_height(Node *n) { return n == NULL ? 0 : n->height; }

    static void clear(Node *p) {
      if (p == NULL)
        return ;
      clear(p->left);
      clear(p->right);
      delete p;
    }

    static Node *deepcopy(Node const *p, Node *pCopyParent, value_compare & comp, allocator_type & alloc) {
      if (p == NULL)
        return (NULL);
      Node *pCopy = new Node(*p->value, comp, alloc);
      pCopy->parent = pCopyParent;
      pCopy->height = p->height;
      pCopy->left = deepcopy(p->left, pCopy, comp, alloc);
      pCopy->right = deepcopy(p->right, pCopy, comp, alloc);
      return pCopy;
    }

    void update_height() { this->height = 1 + std::max(node_height(this->left), node_height(this->right)); }
    int get_balance() { return node_height(this->left) - node_height(this->right); }
    Node *get_last_added() { return this->lastAdded; }
    bool get_one_was_added() { return this->oneWasAdded; }
    allocator_type get_allocator() const { return this->alloc; };
    value_compare get_key_comparator() const { return this->kComp; };
    value_compare get_value_comparator() const { return this->comp; };
    value_type *get_value() const { return this->value; }

    friend bool operator<(Node const & a, value_type const & b) { return a.comp(*a.value, b); }
    friend bool operator<(Node const & a, key_type const & b) { return a.kComp(a.value->first, b); }

    friend bool operator<(value_type const & a, Node const & b) { return b.comp(a, *b.value); }
    friend bool operator<(key_type const & a, Node const & b) { return b.kComp(a, b.value->first); }

    friend bool operator>(Node const & a, value_type const & b) { return a.comp(b, *a.value); }
    friend bool operator>(Node const & a, key_type const & b) { return a.kComp(b, a.value->first); }

    friend bool operator>(value_type const & a, Node const & b) { return b.comp(*b.value, a); }
    friend bool operator>(key_type const & a, Node const & b) { return b.kComp(b.value->first, a); }

    typedef enum {LEFT, RIGHT} branch_dir;

    value_type *value;
    Node *left;
    Node *right;
    Node *parent;
    int height;
    key_compare &kComp;
    value_compare &comp;
    allocator_type &alloc;
    Node *lastAdded;
    bool oneWasAdded;
  };


  BST(const key_compare& kComp = key_compare(),
      allocator_type const & alloc = allocator_type())
    : root(NULL), kComp(kComp), comp(kComp), alloc(alloc), oneWasRemoved(false) {}

  BST(BST const & x): root(NULL), kComp(x.kComp), comp(x.kComp), alloc(x.alloc), oneWasRemoved(x.oneWasRemoved) {
    this->root = Node::deepcopy(x.root, NULL, this->comp, this->alloc);
  }

  ~BST() {
    this->clear();
    this->root = NULL;
  }

  pair<Node*, bool> insert(value_type const & new_val) {
    this->root = Node::insert(this->root, new_val, *this);
    Node *lastAdded = this->root->get_last_added();
    bool oneWasAdded = this->root->get_one_was_added();
    return make_pair<Node*, bool>(lastAdded, oneWasAdded);
  }

  size_type remove(key_type const & kVal) {
    this->root = Node::remove(this->root, kVal, *this);
    if (this->root != NULL)
      this->root->update_height();
    return this->oneWasRemoved ? 1 : 0;
  }

  Node *find(key_type const &kVal) {
      return Node::find(this->root, kVal);
  }

  mapped_type &find_or_insert(key_type const &kVal) {
    Node *n = Node::find(this->root, kVal);
    if (n != NULL) {
      return n->value->second;
    }
    else {
      this->insert(make_pair(kVal, mapped_type())); // BOF
      return this->root->get_last_added()->value->second;
    }
  }

  Node *lower_bound(key_type const &kVal) const {
    return Node::lower_bound(this->root, kVal);
  }

  Node *upper_bound(key_type const &kVal) const {
    return Node::upper_bound(this->root, kVal);
  }

  pair<Node*, Node*> equal_range(key_type const &k) {
    Node *n = this->lower_bound(k);
    if (*n == k) {
      return make_pair(n, n->next());
    }
    return make_pair(n, n);
  }

  size_t get_size() const {
    return Node::get_size(this->root);
  }

  void swap(BST &x) {
    std::swap(this->root, x.root);
  }

  void clear() {
    Node::clear(this->root);
    this->root = NULL;
  }

  bool empty() {
    return this->root == NULL;
  }

  BST &operator=(BST const &x) {
    this->clear();
    this->root = Node::deepcopy(x.root, NULL, this->comp, this->alloc);
    return *this;
  }

  friend bool operator==(BST const & a, BST const & b) { return a.root == b.root; }
  friend bool operator!=(BST const & a, BST const & b) { return a.root != b.root; }

  allocator_type get_allocator() const { return this->alloc; };
  value_compare get_key_comparator() const { return this->kComp; };
  value_compare get_value_comparator() const { return this->comp; };

 private:

  Node *root;
  key_compare kComp;
  value_compare comp;
  allocator_type alloc;
  bool oneWasRemoved;
};

}  // namespace ft

