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

  void remove(value_type const & val) {
    this->root = Node::remove(this->root, val);
  }

  bool empty() {
    return this->root == NULL;
  }

  void _print() {
    if (root != NULL)
      root->_print();
    std::cout << "END" << std::endl;
  }

 private:

  struct Node {
    Node(value_type const & val, value_compare const & comp, allocator_type const & alloc)
      : value(NULL), left(NULL), right(NULL), parent(NULL), height(1), comp(comp), alloc(alloc) {
        this->value = this->alloc.allocate(1);
        this->alloc.construct(this->value, val);
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

    static void setParent(Node *n, Node *p) {
      if (n != NULL)
        n->parent = p;
    }

    static void permute(Node *a, Node *b) {
      std::swap(*a, *b);
      std::swap(a->value, b->value);
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
        p->left = Node::insert(p->left, new_val, bst);
        if (p->left != NULL)
          p->left->parent = p;
      }
      else if (*p < new_val) {
        p->right = Node::insert(p->right, new_val, bst);
        if (p->right != NULL)
          p->right->parent = p;
      }
      else {
        *p->value = new_val;
        return p;
      }
      p->updateHeight();
      int balance = p->getBalance();
      // Left Left Case
      if (balance > 1 && new_val < *p->left) {
        return rotateLeft(p);
      }
      // Left Right Case
      else if (balance > 1 && new_val > *p->left) {
        p->left = rotateLeft(p->left);
        setParent(p->left, p);
        return rotateRight(p);
      }
      // Right Left Case
      else if (balance < -1 && new_val < *p->right) {
        p->right = rotateRight(p->right);
        setParent(p->right, p);
        return rotateLeft(p);
      }
      // Right Right Case
      else if (balance < -1 && new_val > *p->right) {
        return rotateLeft(p);
      }
      return p;
    }

    static Node *remove(Node *p, value_type const &val) {
      if (p == NULL)
        return NULL;

      if (val < *p) {
        p->left = Node::remove(p->left, val);
        if (p->left != NULL) {
          p->left->parent = p;
          p->left->updateHeight();
        }
        return p;
      }
      else if (*p < val) {
        p->right = Node::remove(p->right, val);
        if (p->right != NULL) {
          p->right->parent = p;
          p->right->updateHeight();
        }
        return p;
      }
      else {
        if (p->left == NULL && p->right == NULL) {
          delete p;
          return NULL;
        }
        else if (p->left == NULL) {
          Node *temp = p->right;
          temp->parent = p;
          p->right = NULL;
          delete p;
          return temp;
        }
        else if (p->right == NULL) {
          Node *temp = p->left;
          temp->parent = p;
          p->left = NULL;
          delete p;
          return temp;
        }
        else {
          Node *p_parent = p->parent;
          Node *k = p->next();
          // std::cout << "k = " << *k->value << ", left = " << k->left<< ", right = " << k->right << std::endl;
          std::swap(p->value, k->value);
          p->right = Node::remove(p->right, val);
          if (p->right != NULL) {
            p->right->parent = p;
            p->right->updateHeight();
          }
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

    Node *leftMostChild() {
      if (this->left == NULL)
        return this;
      return this->left->leftMostChild();
    }

    Node *rightMostChild() {
      if (this->right == NULL)
        return this;
      return this->right->rightMostChild();
    }

    bool isLeftChild() {
      return this->parent != NULL && this->parent->left == this;
    }

    bool isRightChild() {
      return this->parent != NULL && this->parent->right == this;
    }

    Node *firstParentLeft() {
      if (this->parent == NULL)
        return NULL;
      if (this->isLeftChild())
        return this->parent;
      return this->parent->firstParentLeft();
    }

    Node *firstParentRight() {
      if (this->parent == NULL)
        return NULL;
      if (this->isRightChild())
        return this->parent;
      return this->parent->firstParentRight();
    }

    Node *next() {
      if (this->right != NULL)
        return this->right->leftMostChild();
      return this->firstParentLeft();
    }

    Node *previous() {
      if (this->left != NULL)
        return this->left->rightMostChild();
      return this->firstParentRight();
    }

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

    // Node const & next() {
    //   Node *n = this;
    //   Node *p;

    //   while (n != NULL) {
    //     if (n->right != NULL)
    //       return n->right;
    //     p = n->parent;
    //     if (p == NULL)
    //       return NULL;
    //     if (n == p->left)
    //       return p;
    //     n = p;
    //   }
    // }

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

