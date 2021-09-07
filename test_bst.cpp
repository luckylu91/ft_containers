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

  srand(time(NULL));
  for (int i = 0; i < 15; ++i)
    bst.insert(i);
  bst._print();

  for (int i = 0; i < 5; i++) {
    int val = rand() % bst.getSize();
    std::cout << "Removing " << val << std::endl;
    bst.remove(val);
    // bst._print();
    bst._print();
  }

  // intBST::NodeIterator iter(bst);
  // printNode(iter.current());
  // iter.next();
  // iter.next();
  // printNode(iter.current());
  // iter.previous();
  // printNode(iter.current());

}
