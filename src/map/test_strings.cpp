#include "test_map.hpp"

void test() {
  map<std::string, std::string> m;

  m["chat"] = "chien";
  m["chat"] = "cheval";
  m["hello"] = "ça va ?";
  print_all_nl(m.begin(), m.end());
}
