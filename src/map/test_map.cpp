#include "map.hpp"
#include <functional>


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

}
