#pragma once
#include <memory>
#include <functional>
#include <cmath>
//
#include <iostream>
#include <iomanip>
#include "pair.hpp"

template <class Value, class ValueCompare = std::less<Value>, class Alloc = std::allocator<Value> >
class BST {
 public:
  typedef Value value_type;
  typedef ValueCompare value_compare;
  typedef Alloc allocator_type;
  class Node;

  BST(value_compare const & comp = value_compare(), allocator_type const & alloc = allocator_type())
    : root(NULL), size(0), comp(comp), alloc(alloc) {}

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

  bool empty() {
    return this->root == NULL;
  }

  size_t getSize() {
    return this->size;
  }

  void _print() {
    if (root != NULL)
      root->_print();
    std::cout << "END" << std::endl;
  }


 public:
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
  //   int height = Node::nodeHeight(this->root);
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

 private:

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

    // void setChild(Node *n, int dir) {
    //   this->_child[dir] = n;
    //   if (n != NULL)
    //     n->_parent = this;
    // }

    static void set_parent(Node *n, Node *p) {
      if (n != NULL)
        n->parent = p;
    }

    static void permute(Node *a, Node *b) {
      std::swap(*a, *b);
      std::swap(a->value, b->value);
    }

    static Node *rotate_left(Node *x) {
      Node *y = x->right;
      Node *yL = y->left;

      x->right = yL;
      set_parent(yL, x);
      y->left = x;
      set_parent(x, y);

      x->update_height();
      y->update_height();
      return y;
    }

    static Node *rotate_right(Node *y) {
      Node *x = y->left;
      Node *xR = x->right;

      y->left = xR;
      set_parent(xR, y);
      x->right = y;
      set_parent(y, x);

      x->update_height();
      y->update_height();
      return x;
    }

    // returns the new root in stead of "p"
    static Node *insert(Node *p, value_type const &new_val, BST &bst) {
      // std::cout << "Inserting " << new_val << std::endl;
      if (p == NULL) {
        bst.size++;
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
        *p->value = new_val;
        p->lastAdded = p;
        p->oneWasAdded = false;
        return p;
      }
      p->update_height();
      int balance = p->get_balance();
      // Left Left Case
      if (balance > 1 && new_val < *p->left) {
        return rotate_left(p);
      }
      // Left Right Case
      else if (balance > 1 && new_val > *p->left) {
        p->left = rotate_left(p->left);
        Node::set_parent(p->left, p);
        return rotate_right(p);
      }
      // Right Left Case
      else if (balance < -1 && new_val < *p->right) {
        p->right = rotate_right(p->right);
        Node::set_parent(p->right, p);
        return rotate_left(p);
      }
      // Right Right Case
      else if (balance < -1 && new_val > *p->right) {
        return rotate_left(p);
      }
      return p;
    }

    static Node *remove(Node *p, value_type const &val, BST &bst) {
      if (p == NULL)
        return NULL;
      if (val < *p) {
        p->left = Node::remove(p->left, val, bst);
        if (p->left != NULL) {
          p->left->parent = p;
          p->left->update_height();
        }
        p->update_height();
        return p;
      }
      else if (*p < val) {
        p->right = Node::remove(p->right, val, bst);
        if (p->right != NULL) {
          p->right->parent = p;
          p->right->update_height();
        }
        p->update_height();
        return p;
      }
      else {
        if (p->left == NULL && p->right == NULL) {
          delete p;
          bst.size--;
          return NULL;
        }
        else if (p->left == NULL) {
          Node *temp = p->right;
          temp->parent = p->parent;
          p->right = NULL;
          delete p;
          bst.size--;

          return temp;
        }
        else if (p->right == NULL) {
          Node *temp = p->left;
          temp->parent = p->parent;
          p->left = NULL;
          delete p;
          bst.size--;
          return temp;
        }
        else {
          Node *p_parent = p->parent;
          Node *k = p->next();
          // std::cout << "k = " << *k->value << ", left = " << k->left<< ", right = " << k->right << std::endl;
          std::swap(p->value, k->value);
          p->right = Node::remove(p->right, val, bst);
          if (p->right != NULL) {
            p->right->parent = p;
            p->right->update_height();
          }
          p->update_height();
          return p;
        }
      }
    }

    // TODO
    Node *find(value_type const & val);

    Node *getIndex(int idx) {
      int lSize = static_cast<int>(this->left->getSize());
      if (idx == lSize)
        return (this);
      else if (idx < lSize)
        return this->left->median(idx);
      else
        return this->right->median(idx - lSize);
    }

    Node *median() {
      return this->getIndex(this->getSize() / 2);
    }

    Node *leftmost_child() {
      if (this->left == NULL)
        return this;
      return this->left->leftmost_child();
    }

    Node *rightmost_child() {
      if (this->right == NULL)
        return this;
      return this->right->rightmost_child();
    }

    bool is_left_child() {
      return this->parent != NULL && this->parent->left == this;
    }

    bool is_right_child() {
      return this->parent != NULL && this->parent->right == this;
    }

    Node *first_parent_left() {
      if (this->parent == NULL)
        return NULL;
      if (this->is_left_child())
        return this->parent;
      return this->parent->first_parent_left();
    }

    Node *first_parent_right() {
      if (this->parent == NULL)
        return NULL;
      if (this->is_right_child())
        return this->parent;
      return this->parent->first_parent_right();
    }
    Node *get_root() {
      if (this->parent == NULL)
        return this;
      return this->parent->get_root();
    }

    Node *next() {
      if (this->right != NULL)
        return this->right->leftmost_child();
      return this->first_parent_left();
    }

    Node *previous() {
      if (this->left != NULL)
        return this->left->rightmost_child();
      return this->first_parent_right();
    }

    static int node_height(Node *n) { return n == NULL ? 0 : n->height; }
    int get_balance() { return node_height(this->left) - node_height(this->right); }
    Node *get_last_added() { return this->lastAdded; }
    bool get_one_was_added() { return this->oneWasAdded; }
    void update_height() { this->height = 1 + std::max(node_height(this->left), node_height(this->right)); }
    allocator_type get_allocator() const { return this->alloc; };
    value_compare get_comparator() const { return this->comp; };
    value_type *get_value() const { return this->value; }

    void _print() {
      if (this->left != NULL)
        this->left->_print();
      std::cout << *value << " (" << this->height << "), ";
      if (this->right != NULL)
        this->right->_print();
    }

    friend bool operator<(Node const & a, value_type const & b) { return a.comp(*a.value, b); }
    friend bool operator<(value_type const & a, Node const & b) { return b.comp(a, *b.value); }
    friend bool operator>(Node const & a, value_type const & b) { return a.comp(b, *a.value); }
    friend bool operator>(value_type const & a, Node const & b) { return b.comp(*b.value, a); }

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

 private:
  Node *root;
  size_t size;
  value_compare comp;
  allocator_type alloc;
};

