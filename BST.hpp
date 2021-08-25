#pragma once
#include <memory>
#include <functional>
//
#include <cmath>
#include <iostream>

template <class Value, class ValueCompare = std::less<Value>, class Alloc = std::allocator<Value> >
class BST {
 public:
  typedef Value value_type;
  typedef ValueCompare value_compare;

  BST() : root(NULL) {}

  void insert(value_type const & val) {
    value_type *val_ptr = new value_type(val);
    if (root == NULL)
      root = new Node(val_ptr);
    else
      root->insert(val_ptr);
  }

  void _print() {
    if (root != NULL)
      root->_print(0);
    std::cout << "END" << std::endl;
  }

 private:
  class Node {
   public:
    Node(value_type *val) : _value(val), _parent(NULL), _comp(value_compare()), _height(0) { _child[0] = _child[1] = NULL; }

    Node *find(value_type const & val);

    Node *rotateLeft(Node )
    // void setChild(Node *N, int dir) {
    //   this->child[dir] = N;
    //   if (N != NULL) {
    //     N->parent = this;
    //   }
    // }

    // dir is left (i.e. 0) if this is the right child of its parent
    // void rotate(int dir) {
    //   int balance_update = 2 * dir - 1;
    //   Node *P = this->parent;

    //   P->setChild(this->child[dir], 1-dir);
    //   this->setChild(P, dir);
    //   this->parent = P->parent;
    //   // P->parent->child[] = this;
    //   P->balance += balance_update;
    //   this->balance += balance_update;
    // }

    // // This(left child of Parent) -(parent-right)-> P -(parent-left)-> Right Child
    // void rotateRight() {
    //   Node *P = this->parent;

    //   P->setChild(this->child[1], 0);
    //   P->balance += 1;
    //   this->setChild(P, 1);
    //   this->balance += 1;
    // }

    // // This(right child of Parent) -(parent-left)-> P -(parent-right)-> Left Child
    // void rotateLeft() {
    //   Node *P = this->parent;

    //   P->setChild(this->child[0], 1);
    //   P->balance -= 1;
    //   this->setChild(P, 0);
    //   this->balance -= 1;
    // }

    // void add(value_type *val) {
    //   if (this->comp(*this->value, *val)) {
    //     if (child[0] == NULL)
    //       this->setChild(new Node(val), 0);
    //     else {
    //       child[0]->add(val);
    //       this->balance -= 1;
    //       if (this->balance == -2) {
    //         child[0]->rotateRight();
    //       }
    //     }
    //   }
    //   else if (this->comp(*val, *this->value)) {
    //     if (child[1] == NULL)
    //       this->setChild(new Node(val), 1);
    //     else {
    //       child[1]->add(val);
    //       this->balance += 1;
    //       if (this->balance == 2) {
    //         child[1]->rotateLeft();
    //       }
    //     }
    //   }
    //   else {
    //     *value = *val;
    //   }
    // }

    // bool insert(value_type *val) {
    //   std::cout << "Inserting " << *val << " (Node " << *this->value << ")" << std::endl;
    //   int balance_update;
    //   int dir;
    //   bool is_equal = true;

    //   if (this->comp(*val, *this->value)) {
    //     dir = 0;
    //     balance_update = -1;
    //     is_equal = false;
    //   }
    //   else if (this->comp(*this->value, *val)) {
    //     dir = 1;
    //     balance_update = 1;
    //     is_equal = false;
    //   }
    //   if (is_equal) {
    //     std::cout << "Is equal" << std::endl;
    //     *this->value = *val;
    //     return false;
    //   }
    //   else {
    //     if (child[dir] == NULL)
    //     {
    //       std::cout << "Insertion to the " << (dir == 0 ? "left" : "right") << " of node " << *this->value << std::endl;
    //       this->setChild(new Node(val), dir);
    //       this->balance += balance_update;
    //       return true;
    //     }
    //     bool balance_changed = child[dir]->insert(val);
    //     if (balance_changed) {
    //       std::cout << "New value affection balance" << std::endl;
    //       this->balance += balance_update;
    //       if (this->balance == -2 || this->balance == 2) {
    //         std::cout << "Rotating node " << *child[dir]->value << " with arg " << 1-dir << std::endl;
    //         std::cout << "node's parent : " << *child[dir]->parent->value << ", ";
    //         std::cout << "as " << this->_parentSideStr() << " child" << std::endl;
    //         child[dir]->rotate(1-dir);
    //       }
    //     }
    //     return balance_changed;
    //   }
    // }

    void _print(int level) {
      if (this->_child[0] != NULL)
        this->_child[0]->_print(level + 1);
      std::cout << *_value << " (" << level << "), ";
      if (this->_child[1] != NULL)
        this->_child[1]->_print(level + 1);
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

   private:
    value_type *_value;
    Node *_parent;
    Node *_child[2];
    value_compare _comp;
    int _height;
  };

  Node *root;
};
