#include "BST.hpp"
#include <functional>

int main()
{
  BST< int, std::less<int> > bst;

  bst.insert(0);
  bst.insert(1);
  bst.insert(-1);
  bst.insert(2);
  bst.insert(2);
  bst.insert(3);
  bst._print();
}
