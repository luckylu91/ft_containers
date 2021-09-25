#pragma once
#include "test_all.h"
#ifdef MINE
  #include "map.hpp"
  // using ft::pair;
  // using ft::make_pair;
  // using ft::map;
  using namespace ft;
#else
  #include <map>
  // using std::pair;
  // using std::make_pair;
  // using std::map;
  using namespace std;
#endif

template <class C1, class C2>
std::ostream & operator<<(std::ostream & os, pair<C1, C2> const & p) {
  os << "(" << p.first << "," << p.second << ")";
  return os;
}

#include "test_utils.h"

struct KeyCompareInt {
  bool operator() (int x, int y) const { return -x / 2 < - y / 2; }
};
struct KeyCompareStr {
  bool operator() (std::string x, std::string y) const {
    return (x.empty() && !y.empty()) || (!x.empty() && !y.empty() && x[0] < y[0]);
  }
};

typedef map<int, int>::iterator   iterator_type;
typedef pair<iterator_type, bool> insert_return_type;

template <class T1, class T2, class Comp>
void insert(map<T1, T2, Comp> & container, T1 k, T2 v) {
  pair<T1, T2> val = make_pair(k, v);
  std::cout << "Inserting " << val << std::endl;

  pair<typename map<T1, T2, Comp>::iterator, bool> ret = container.insert(val);

  std::cout << "Was present : " << ret.second << std::endl;
  std::cout << "Iterator points to " << *ret.first << std::endl;
}
