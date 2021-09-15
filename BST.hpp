#pragma once
#include <memory>
#include <functional>
#include <cmath>
//
#include <iostream>
#include <iomanip>
#include "pair.hpp"

template <class Key, class T, class KeyCompare, class Alloc> class map;




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
