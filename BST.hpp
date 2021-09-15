#pragma once
#include <memory>
#include <functional>
#include <cmath>
//
#include <iostream>
#include <iomanip>
#include "pair.hpp"

template <class KeyType, class MappedType, class KeyCompare, class ValueCompare, class Alloc>
class BST {
 public:
  typedef KeyType key_type;
  typedef MappedType mapped_type;
  typedef pair<const key_type, mapped_type> value_type;
  typedef KeyCompare key_compare;
  typedef ValueCompare value_compare;
  typedef Alloc allocator_type;

  struct Node {
    Node(value_type const & val, value_compare & comp, allocator_type & alloc)
      : value(NULL), left(NULL), right(NULL), parent(NULL), height(1), comp(comp), alloc(alloc), oneWasAdded(true) {
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

      x->update_height();
      y->update_height();
      set_parent(x, yOldParent);
      return x;
    }

    static Node *do_rebalance_cases(Node *p, bool isLeft1, bool isLeft2) {
      // Left Left Case
      if (isLeft1 && isLeft2) {
        return rotate_left(p);
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
      // std::cout << "Inserting " << new_val << std::endl;
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
        p->value->second = new_val.second;
        p->lastAdded = p;
        p->oneWasAdded = false;
        return p;
      }
      p->update_height();
      int balance = p->get_balance();
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
    static Node *remove(Node *p, value_type const &val, BST &bst) {
      if (p == NULL)
        return NULL;
      if (val < *p) {
        p->left = Node::remove(p->left, val, bst);
      }
      else if (*p < val) {
        p->right = Node::remove(p->right, val, bst);
      }
      else {
        if (p->left == NULL && p->right == NULL) {
          delete p;
          bst.size--;
          return NULL;
        }
        else if (p->left == NULL || p->right == NULL) {
          bst.size--;
          return Node::move_only_child_up(p);
        }
        else {
          Node *p_parent = p->parent;
          Node *k = p->next();
          std::swap(p->value, k->value);
          p->right = Node::remove(p->right, val, bst);
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

    static size_t get_size(Node *p) {
      if (p == NULL)
        return (0);
      return (1 + Node::get_size(p->left) + Node::get_size(p->right));
    }

    // Node *getIndex(int idx) {
    //   int lSize = static_cast<int>(this->left->getSize());
    //   if (idx == lSize)
    //     return (this);
    //   else if (idx < lSize)
    //     return this->left->median(idx);
    //   else
    //     return this->right->median(idx - lSize);
    // }

    // Node *median() {
    //   return this->getIndex(this->getSize() / 2);
    // }

    Node *leftmost_child() const {
      if (this->left == NULL)
        return this;
      return this->left->leftmost_child();
    }

    Node *rightmost_child() const {
      if (this->right == NULL)
        return this;
      return this->right->rightmost_child();
    }

    bool is_left_child() const {
      return this->parent != NULL && this->parent->left == this;
    }

    bool is_right_child() const {
      return this->parent != NULL && this->parent->right == this;
    }

    Node *first_parent_left() const {
      if (this->parent == NULL)
        return NULL;
      if (this->is_left_child())
        return this->parent;
      return this->parent->first_parent_left();
    }

    Node *first_parent_right() const {
      if (this->parent == NULL)
        return NULL;
      if (this->is_right_child())
        return this->parent;
      return this->parent->first_parent_right();
    }
    Node *get_root() const {
      if (this->parent == NULL)
        return this;
      return this->parent->get_root();
    }

    Node *next() const {
      if (this->right != NULL)
        return this->right->leftmost_child();
      return this->first_parent_left();
    }

    Node *previous() const {
      if (this->left != NULL)
        return this->left->rightmost_child();
      return this->first_parent_right();
    }

    static int node_height(Node *n) { return n == NULL ? 0 : n->height; }

    void update_height() { this->height = 1 + std::max(node_height(this->left), node_height(this->right)); }

    static void clear(Node *p) {
      if (p == NULL)
        return ;
      clear(p->left);
      clear(p->right);
      delete p;
    }

    static Node *deepcopy(Node const *p, Node const *pCopyParent, value_compare & comp, allocator_type & alloc) {
      if (p == NULL)
        return (NULL);
      Node *pCopy = new Node(*p->value, comp, alloc);
      pCopy->parent = pCopyParent;
      pCopy->height = p->height;
      pCopy->left = deepcopy(p->left, pCopy, comp, alloc);
      pCopy->right = deepcopy(p->right, pCopy, comp, alloc);
    }

    int get_balance() { return node_height(this->left) - node_height(this->right); }
    Node *get_last_added() { return this->lastAdded; }
    bool get_one_was_added() { return this->oneWasAdded; }
    allocator_type get_allocator() const { return this->alloc; };
    value_compare get_key_comparator() const { return this->kComp; };
    value_compare get_value_comparator() const { return this->comp; };
    value_type *get_value() const { return this->value; }

    void _print() {
      if (this->left != NULL)
        this->left->_print();
      std::cout << *value << " (" << this->height << "), ";
      if (this->right != NULL)
        this->right->_print();
    }

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
    value_compare &comp;
    allocator_type &alloc;
    Node *lastAdded;
    bool oneWasAdded;
  };


  BST(const key_compare& kComp = key_compare(),
      allocator_type const & alloc = allocator_type())
    : root(NULL), kComp(kComp), comp(kComp), alloc(alloc) {}

  BST(BST const & x): root(NULL), kComp(x.kComp), comp(x.kComp), alloc(x.alloc) {
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

  void remove(value_type const & val) {
    this->root = Node::remove(this->root, val, *this);
    if (this->root != NULL)
      this->root->update_height();
  }

  Node *find(key_type const &kVal) {
      return Node::find(this->root, kVal);
  }

  mapped_type &find_or_insert(key_type const &kVal) {
    Node *n = Node::find(this->root, kVal);
    if (n != NULL) {
      return n->value.second;
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

  size_t get_size() {
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
  }

  allocator_type get_allocator() const { return this->alloc; };
  value_compare get_key_comparator() const { return this->kComp; };
  value_compare get_value_comparator() const { return this->comp; };

  void _print() {
    if (root != NULL)
      root->_print();
    std::cout << "END" << std::endl;
  }

 private:

  Node *root;
  key_compare kComp;
  value_compare comp;
  allocator_type alloc;
};


// ITERATOR

//   struct NodeList {
//     NodeList(Node *head, NodeList *tail) : head(head), tail(tail) {}

//     NodeList(NodeList const & other) : head(other.head), tail(new NodeList(*other.tail)) {}
//
//     NodeList & operator=(NodeList const & other) {
//       if (this->tail != NULL)
//         delete this->tail;
//       this->head = other.head;
//       this->tail = new NodeList(*other.tail);
//       return *this;
//     }
//
//     ~NodeList() {
//       delete this->tail;
//     }
//
//     static void push(NodeList **lA, NodeList **lB) {
//       if (lA != NULL) {
//         NodeList *nl = *lA;
//         *lA = (*lA)->tail;
//         nl->tail = *lB;
//         *lB = nl;
//       }
//     }
//
//     Node *head;
//     NodeList *tail;
//   };

//   class NodeBiStack {
//   public:
//     NodeBiStack() : listA(NULL), listB(NULL) {}
//
//     NodeBiStack(NodeBiStack const & other) : listA(*other.listA), listB(*other.listB) {}
//
//     NodeBiStack & operator=(NodeBiStack const & other) {
//       if (this->listA != NULL)
//         delete this->listA;
//       if (this->listB != NULL)
//         delete this->listB;
//       this->listA = new NodeBiStack(*other.listA);
//       this->listB = new NodeBiStack(*other.listB);
//       return *this;
//     }
//
//     ~NodeBiStack() {
//       if (this->listA != NULL)
//         delete this->listA;
//       if (this->listB != NULL)
//         delete this->listB;
//     }
//
//     void push(Node *n) {
//       this->listA = new NodeList(n, this->listA);
//     }
//
//     void pushB() {
//       NodeList::push(&this->listA, &this->listB);
//     }
//
//     void pushA() {
//       NodeList::push(&this->listB, &this->listA);
//     }
//
//     Node *top() {
//       if (this->listA != NULL)
//         return this->listA->head;
//       else
//         return NULL;
//     }
//
//     bool isEnd() {
//       return this->listA == NULL;
//     }
//
//   private:
//     NodeList *listA;
//     NodeList *listB;
//   };

//  public:
//   // src https://www.geeksforgeeks.org/implementing-forward-iterator-in-bst/
//   class NodeIterator {
//    public:
//     NodeIterator(BST const & bst, bool reverse = false) : reverse(reverse) {
//       Node *n = bst.root;
//       while (n != NULL) {
//         stack.push(n);
//         n = !this->reverse ? n->left : n->right;
//       }
//     }
//
//     NodeIterator(NodeIterator const & other) : stack(other.stack), reverse(other.reverse) {}
//
//     NodeIterator & operator=(NodeIterator const & other) {
//       this->stack = NodeBiStack(other.stack);
//       return *this;
//     }
//
//     ~NodeIterator() {}
//
//     Node *current() {
//       return stack.top();
//     }
//
//     void next() {
//       Node *curr = !this->reverse ? this->current()->right : this->current()->left;
//       this->stack.pushB();
//       while (curr != NULL) {
//         this->stack.push(curr);
//         curr = !this->reverse ? curr->left : curr->right;
//       }
//     }
//
//     void previous() {
//       this->stack.pushA();
//     }
//
//     // bool isEnd() {
//     //   return this->stack.isEnd();
//     // }
//
//     bool isReverse() {
//       return this->reverse;
//     }
//
//     bool operator==(NodeIterator const & other) {
//       return this->stack.top() == other.stack.top();
//     }
//
//     bool operator!=(NodeIterator const & other) {
//       return !this->operator==(other);
//     }
//
//   private:
//     NodeBiStack stack;
//     bool reverse;
//   };

// PRINT

  // void _fillMatrixRepr(int **matrix, int h, Node *n, int inv_height, int *indices) {
  //   if (n == NULL)
  //     return;
  //   _fillMatrixRepr(matrix, h, n->left, inv_height + 1, indices);
  //   matrix[inv_height][indices[inv_height]] = *n->get_value();
  //   indices[inv_height]++;
  //   _fillMatrixRepr(matrix, h, n->right, inv_height + 1, indices);
  // }

  // void _printNSpaces(int n) {
  //   for (int i = 0; i < n; i++) {
  //     std::cout << " ";
  //   }
  // }

  // size_t _findMaxNumberLenght(int **matrix,  int h, int *indices) {
  //   size_t maxLength = 0;
  //   for (int i = 0; i < h; i++) {
  //     for (int j = 0; j < indices[i]; j++) {
  //       maxLength = std::max(maxLength, std::to_string(matrix[i][j]).length());
  //     }
  //   }
  //   return maxLength;
  // }

  // // Multiply distances with max { strlen(itoa(value)) }
  // void _prettyPrint() {
  //   // int numberLeaves = _numberOfLeaves(this->root);
  //   int height = Node::node_height(this->root);
  //   int numberLeaves = 1 << height;
  //   int **matrix = new int*[height];
  //   for (int i = 0; i < height; i++) {
  //     matrix[i] = new int[numberLeaves]();
  //   }
  //   int *indices = new int[height]();
  //   _fillMatrixRepr(matrix, height, this->root, 0, indices);
  //   int maxLength = static_cast<int>(_findMaxNumberLenght(matrix, height, indices));
  //   for (int i = 0; i < height; i++) {
  //     int nH = height - 1 - i;
  //     _printNSpaces(((1 << nH) - 1) * maxLength);
  //     for (int j = 0; j < indices[i]; j++) {
  //       std::cout << std::setw(maxLength) << matrix[i][j];
  //       if (j < indices[i] - 1)
  //         _printNSpaces(((1 << (nH + 1)) - 1) * maxLength);
  //     }
  //     std::cout << std::endl;
  //   }
  // }
