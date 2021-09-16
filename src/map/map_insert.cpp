#include "test_map.h"

typedef map<int, int>::iterator   iterator_type;
typedef pair<iterator_type, bool> insert_return_type;

void insert(map<int, int> & container, int k, int v) {
  pair<int, int> val = make_pair(k, v);
  std::cout << "Inserting " << val << std::endl;

  insert_return_type ret = container.insert(val);

  std::cout << "Was present : " << ret.second << std::endl;
  std::cout << "Iterator points to " << *ret.first << std::endl;
}

void test()
{
  map<int, int> m0;

  std::boolalpha(std::cout);
  for (int i = 0; i < 5; ++i) {
    insert(m0, i, i);
  }
  for (int i = 0; i < 5; ++i) {
    insert(m0, i, 2 * i);
  }
}
