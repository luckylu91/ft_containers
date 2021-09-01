#include "BST.hpp"
#include <functional>

template <class T> void printNode(T *n) {
  if (n == NULL)
    std::cout << "NULL" << std::endl;
  else {
    std::cout << *n->value << std::endl;
  }
}

int main()
{
  typedef BST< int, std::less<int> > intBST;
  intBST bst;

  for (int i = 0; i < 100; ++i)
    bst.insert(i);
  // bst.insert(0);
  // bst.insert(1);
  // bst.insert(-1);
  // bst.insert(2);
  // bst.insert(2);
  // bst.insert(3);
  bst._print();

  // intBST::NodeIterator iter(bst);
  // printNode(iter.current());
  // iter.next();
  // iter.next();
  // printNode(iter.current());
  // iter.previous();
  // printNode(iter.current());
  
}
