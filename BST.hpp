#pragma once
#include <memory>
#include <functional>
#include <cmath>
//
#include <iostream>

template <class Value, class ValueCompare = std::less<Value>, class Alloc = std::allocator<Value> >
class BST {
 public:
  typedef Value value_type;
  typedef ValueCompare value_compare;
  typedef Alloc allocator_type;

  BST(value_compare const & comp = value_compare(), allocator_type const & alloc = allocator_type())
    : root(NULL), comp(comp), alloc(alloc) {}

  void insert(value_type const & new_val) {
    this->root = Node::insert(this->root, new_val, *this);
  }

  void _print() {
    if (root != NULL)
      root->_print(0);
    std::cout << "END" << std::endl;
  }

 private:
  class Node {
   public:
    Node(value_type const & val, value_compare & comp, allocator_type & alloc)
      : value(NULL), left(NULL), right(NULL), parent(NULL), height(0), comp(comp), alloc(alloc) {
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

    static void setParent(Node *n, Node *p) {
      if (n != NULL)
        n->parent = p;
    }

    static Node *rotateLeft(Node *x) {
      Node *y = x->right;
      Node *yL = y->left;

      x->right = yL;
      setParent(yL, x);
      y->left = x;
      setParent(x, y);

      x->updateHeight();
      y->updateHeight();
      return y;
    }

    static Node *rotateRight(Node *y) {
      Node *x = y->left;
      Node *xR = x->right;

      y->left = xR;
      setParent(xR, y);
      x->right = y;
      setParent(y, x);

      x->updateHeight();
      y->updateHeight();
      return x;
    }

    // returns the new root in stead of "p"
    static Node *insert(Node *p, value_type const &new_val, BST const & bst) {
      std::cout << "Inserting " << new_val << std::endl;

      if (p == NULL)
        return new Node(new_val, bst.comp, bst.alloc);
      if (new_val < *p) {
        p->left = insert(p->left, new_val);
        setParent(p->left, p);
      }
      else if (*p < new_val) {
        p->right = insert(p->right, new_val);
        setParent(p->right, p);
      }
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
        return rotateLeft(p);
      }
      // Left Right Case
      else if (balance > 1 && new_val > *p->left) {
        std::cout << "Left Right Case" << std::endl;
        p->left = rotateLeft(p->left);
        setParent(p->left, p);
        return rotateRight(p);
      }
      // Right Left Case
      else if (balance < -1 && new_val < *p->right) {
        std::cout << "Right Left Case" << std::endl;
        p->right = rotateRight(p->right);
        setParent(p->right, p);
        return rotateLeft(p);
      }
      // Right Right Case
      else if (balance < -1 && new_val > *p->right) {
        std::cout << "Right Right Case" << std::endl;
        return rotateLeft(p);
      }
      return p;
    }

    // TODO
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

    allocator_type get_allocator() const { return this->alloc; };
    value_compare get_comparator() const { return this->comp; };
    value_type *get_value() const { return this->value; }

    void _print(int level) {
      if (this->left != NULL)
        this->left->_print(level + 1);
      std::cout << *value << " (" << level << "), ";
      if (this->right != NULL)
        this->right->_print(level + 1);
    }

    friend bool operator<(Node const & a, value_type const & b) { return a.comp(*a.value, b); }
    friend bool operator<(value_type const & a, Node const & b) { return b.comp(a, *b.value); }
    friend bool operator>(Node const & a, value_type const & b) { return a.comp(b, *a.value); }
    friend bool operator>(value_type const & a, Node const & b) { return b.comp(*b.value, a); }

    Node const & next() {
      Node *n = this;
      Node *p;

      while (n != NULL) {
        if (n->right != NULL)
          return n->right;
        p = n->parent;
        if (p == NULL)
          return NULL;
        if (n == p->left)
          return p;
        n = p;
      }
    }

   private:
    value_type *value;
    Node *left;
    Node *right;
    Node *parent;
    int height;
    value_compare &comp;
    allocator_type &alloc;
  };

  class NodeStack {
  public:
    NodeStack() : list(NULL) {}
    ~NodeStack() {}

    void push(Node *n) {
      this->list = new NodeList(n, this->list);
    }

    void pop() {
      NodeList *nl = this->list;
      this->list = this->list->tail;
      delete nl;
    }

    Node *top() {
      return (this->list->head);
    }

  private:
    struct NodeList {
      NodeList(Node *head, NodeList *tail) : head(head), tail(tail) {}
      ~NodeList() {}
      Node *head;
      NodeList *tail;
    }

    NodeList *list;
  }

  // src https://www.geeksforgeeks.org/implementing-forward-iterator-in-bst/
  class NodeIterator {
    NodeIterator(BST const & bst) {
      Node *n = bst.root;

      while (n != NULL) {
        stack.push(n);
        n = n->left;
      }
    }
    ~NodeIterator()
    Node *curr();
    void next();
    bool isEnd();
  private:
    NodeStack stack;
  }

 private:
  Node *root;
  value_compare comp;
  allocator_type alloc;
};

