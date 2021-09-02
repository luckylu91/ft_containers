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

  struct Node {
    Node(value_type const & val, value_compare const & comp, allocator_type const & alloc)
      : value(NULL), left(NULL), right(NULL), parent(NULL), height(0), comp(comp), alloc(alloc) {
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
      // std::cout << "Inserting " << new_val << std::endl;

      if (p == NULL)
        return new Node(new_val, bst.comp, bst.alloc);
      if (new_val < *p) {
        p->left = insert(p->left, new_val, bst);
        setParent(p->left, p);
      }
      else if (*p < new_val) {
        p->right = insert(p->right, new_val, bst);
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
        // std::cout << "Left Left Case" << std::endl;
        return rotateLeft(p);
      }
      // Left Right Case
      else if (balance > 1 && new_val > *p->left) {
        // std::cout << "Left Right Case" << std::endl;
        p->left = rotateLeft(p->left);
        setParent(p->left, p);
        return rotateRight(p);
      }
      // Right Left Case
      else if (balance < -1 && new_val < *p->right) {
        // std::cout << "Right Left Case" << std::endl;
        p->right = rotateRight(p->right);
        setParent(p->right, p);
        return rotateLeft(p);
      }
      // Right Right Case
      else if (balance < -1 && new_val > *p->right) {
        // std::cout << "Right Right Case" << std::endl;
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

    value_type *value;
    Node *left;
    Node *right;
    Node *parent;
    int height;
    value_compare comp;
    allocator_type alloc;
  };

  struct NodeList {
    NodeList(Node *head, NodeList *tail) : head(head), tail(tail) {}

    NodeList(NodeList const & other) : head(other.head), tail(new NodeList(*other.tail)) {}

    NodeList & operator=(NodeList const & other) {
      if (this->tail != NULL)
        delete this->tail;
      this->head = other.head;
      this->tail = new NodeList(*other.tail);
      return *this;
    }

    ~NodeList() {
      delete this->tail;
    }

    static void push(NodeList **lA, NodeList **lB) {
      if (lA != NULL) {
        NodeList *nl = *lA;
        *lA = (*lA)->tail;
        nl->tail = *lB;
        *lB = nl;
      }
    }

    Node *head;
    NodeList *tail;
  };

  class NodeBiStack {
  public:
    NodeBiStack() : listA(NULL), listB(NULL) {}

    NodeBiStack(NodeBiStack const & other) : listA(*other.listA), listB(*other.listB) {}

    NodeBiStack & operator=(NodeBiStack const & other) {
      if (this->listA != NULL)
        delete this->listA;
      if (this->listB != NULL)
        delete this->listB;
      this->listA = new NodeBiStack(*other.listA);
      this->listB = new NodeBiStack(*other.listB);
      return *this;
    }

    ~NodeBiStack() {
      if (this->listA != NULL)
        delete this->listA;
      if (this->listB != NULL)
        delete this->listB;
    }

    void push(Node *n) {
      this->listA = new NodeList(n, this->listA);
    }

    void pushB() {
      NodeList::push(&this->listA, &this->listB);
    }

    void pushA() {
      NodeList::push(&this->listB, &this->listA);
    }

    Node *top() {
      if (this->listA != NULL)
        return this->listA->head;
      else
        return NULL;
    }

    bool isEnd() {
      return this->listA == NULL;
    }

  private:
    NodeList *listA;
    NodeList *listB;
  };

  //
 public:
  // src https://www.geeksforgeeks.org/implementing-forward-iterator-in-bst/
  class NodeIterator {
   public:
    NodeIterator(BST const & bst, bool reverse = false) : reverse(reverse) {
      Node *n = bst.root;
      while (n != NULL) {
        stack.push(n);
        n = !this->reverse ? n->left : n->right;
      }
    }

    NodeIterator(NodeIterator const & other) : stack(other.stack), reverse(other.reverse) {}

    NodeIterator & operator=(NodeIterator const & other) {
      this->stack = NodeBiStack(other.stack);
      return *this;
    }

    ~NodeIterator() {}

    Node *current() {
      return stack.top();
    }

    void next() {
      Node *curr = !this->reverse ? this->current()->right : this->current()->left;
      this->stack.pushB();
      while (curr != NULL) {
        this->stack.push(curr);
        curr = !this->reverse ? curr->left : curr->right;
      }
    }

    void previous() {
      this->stack.pushA();
    }

    // bool isEnd() {
    //   return this->stack.isEnd();
    // }

    bool isReverse() {
      return this->reverse;
    }

    bool operator==(NodeIterator const & other) {
      return this->stack.top() == other.stack.top();
    }

    bool operator!=(NodeIterator const & other) {
      return !this->operator==(other);
    }

  private:
    NodeBiStack stack;
    bool reverse;
  };

 private:
  Node *root;
  value_compare comp;
  allocator_type alloc;
};

