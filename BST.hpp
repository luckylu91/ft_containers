#pragma once
#include <memory>
#include <functional>
//
#include <cmath>
#include <iostream>

template <class Value, class ValueCompare = std::less<Value>, class Alloc = std::allocator<Value> >
class BST {
 public:
  typedef Alloc allocator_type;
  typedef Value value_type;
  typedef ValueCompare value_compare;

  BST(allocator_type const & alloc = allocator_type()) : root(NULL), alloc(alloc) {}

  void insert(value_type const & new_val) {
    this->root = Node::insert(this->root, new_val);
  }

  void _print() {
    if (root != NULL)
      root->_print(0);
    std::cout << "END" << std::endl;
  }

 private:
  class Node {
   public:
    Node(value_type const &val, allocator_type const & alloc = allocator_type())
      : value(NULL), left(NULL), right(NULL), comp(value_compare()), height(0), alloc(alloc) {
        std::cout << "Node constructor OK" << std::endl;
        this->value = this->alloc.allocate(1);
        this->alloc.construct(this->value, val);
    }

    ~Node() {
      alloc.destruct(this->value);
      alloc.deallocate(this->value);
    }

    // void setChild(Node *n, int dir) {
    //   this->_child[dir] = n;
    //   if (n != NULL)
    //     n->_parent = this;
    // }

    static Node *rotateLeft(Node *x) {
      Node *y = x->right;
      Node *yL = y->left;

      x->right = yL;
      y->left = x;

      x->updateHeight();
      y->updateHeight();
      return y;
    }

    static Node *rotateRight(Node *y) {
      Node *x = y->left;
      Node *xR = x->right;

      y->left = xR;
      x->right = y;
      
      x->updateHeight();
      y->updateHeight();
      return x;
    }

    // returns the new root in stead of "p"
    static Node *insert(Node *p, value_type const &new_val) {
      std::cout << "Inserting " << new_val << std::endl;

      if (p == NULL)
        return new Node(new_val);
      if (new_val < *p)
        p->left = insert(p->left, new_val);
      else if (*p < new_val)
        p->right = insert(p->right, new_val);
      else {
        *p->value = new_val;
        return p;
      }

      p->updateHeight();
      // p->height = 1 + std::max(nodeHeight(p->left), nodeHeight(p->right));
      int balance = p->getBalance();
      // Left Left Case
      if (balance > 1 && new_val < *p->left) {
        std::cout << "Left Left Case" << std::endl;
        return rotateLeft(p); }
      // Left Right Case
      else if (balance > 1 && new_val > *p->left) {
        std::cout << "Left Right Case" << std::endl;
        p->left = rotateLeft(p->left);
        return rotateRight(p);
      }
      // Right Left Case
      else if (balance < -1 && new_val < *p->right) {
        std::cout << "Right Left Case" << std::endl;
        p->right = rotateRight(p->right);
        return rotateLeft(p);
      }
      // Right Right Case
      else if (balance < -1 && new_val > *p->right) {
        std::cout << "Right Right Case" << std::endl;
        return rotateLeft(p); }
      return p;
    }

    Node *find(value_type const & val);

    static int nodeHeight(Node *n) {
      if (n == NULL)
        return 0;
      return n->height;
    }

    int getBalance() {
      return nodeHeight(this->left) - nodeHeight(this->right);
    }

    void updateHeight() {
      this->height = 1 + std::max(nodeHeight(this->left), nodeHeight(this->right));
    }

    void _print(int level) {
      if (this->left != NULL)
        this->left->_print(level + 1);
      std::cout << *value << " (" << level << "), ";
      if (this->right != NULL)
        this->right->_print(level + 1);
    }

    // int _parentSide() {
    //   if (this->parent == NULL)
    //     return 0;
    //   if (this->parent->child[0] == this)
    //     return -1;
    //   else
    //     return 1;
    // }

    // std::string _parentSideStr() {
    //   switch (this->_parentSide()) {
    //     case -1:
    //       return "left";
    //     case 1:
    //       return "right";
    //     default:
    //       return "none";
    //   }
    // }

    friend bool operator<(Node const & a, value_type const & b) { return a.comp(*a.value, b); }
    friend bool operator<(value_type const & a, Node const & b) { return b.comp(a, *b.value); }
    friend bool operator>(Node const & a, value_type const & b) { return a.comp(b, *a.value); }
    friend bool operator>(value_type const & a, Node const & b) { return b.comp(*b.value, a); }
    // friend static bool operator==(Node const & a, Node const & b) { !(*a < *b) && !(*b < *a); }

   private:
    value_type *value;
    Node *left;
    Node *right;
    value_compare comp;
    int height;
    allocator_type alloc;
  };

  Node *root;
  allocator_type alloc;
};
