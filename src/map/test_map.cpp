#include "map.hpp"
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
  typedef ft::map<int, int> mapInt;
  mapInt m;

  srand(time(NULL));
  for (int i = 0; i < 15; ++i) {
    std::cout << i << std::endl;
    m.insert(make_pair(i, i));
  }
  // m.insert(make_pair(1, 1));


  // for (int i = 0; i < 5; i++) {
  //   int val = rand() % m.getSize();
  //   std::cout << "Removing " << val << std::endl;
  //   m.remove(val);
  //   // bst._print();
  //   m._prettyPrint();
  // }

  // intBST::NodeIterator iter(bst);
  // printNode(iter.current());
  // iter.next();
  // iter.next();
  // printNode(iter.current());
  // iter.previous();
  // printNode(iter.current());

}
