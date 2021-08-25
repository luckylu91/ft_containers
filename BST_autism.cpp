#include <functional>
//
#include <cmath>
#include <iostream>

struct Tree {
  Tree *child[2] = {NULL, NULL};
  Tree *parent = NULL;

  //
  void rotateLeft() {
    Tree *LC = child[0];
    Tree *P = parent;
    Tree *T = this;

    T->child[0] = P;
    P->parent = T;
    P->child[1] = LC;
    LC->parent = P;
    std::swap(*P, *T);
  }
}

int main() {

}
