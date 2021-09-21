#include "test_vector.h"

template<typename T, size_t n>
size_t length(T (*)[n]) {
  return n;
}

template<typename T, size_t n>
int *end(T (*array)[n]) {
  return *array + n;
}

void all_comparisons(vector<int> const & a, vector<int> const & b) {
  std::boolalpha(std::cout);
  std::cout << "a = ";
  print_vect(a);
  std::cout << ", b = ";
  print_vect(b);
  std::cout << std::endl;
  std::cout << "a == b : " << (a == b) << std::endl;
  std::cout << "a != b : " << (a != b) << std::endl;
  std::cout << "a < b : " << (a < b) << std::endl;
  std::cout << "a > b : " << (a > b) << std::endl;
  std::cout << "a >= b : " << (a >= b) << std::endl;
  std::cout << "a <= b : " << (a <= b) << std::endl;
}

void test() {
  int v1_values[] = {0, 1, 2, 3};
  vector<int> v1(v1_values, end(&v1_values));
  int v1b_values[] = {0, 1, 2, 3};
  vector<int> v1b(v1b_values, end(&v1b_values));
  int v2_values[] = {0, 1, 2, 3, 4};
  vector<int> v2(v2_values, end(&v2_values));
  int v2b_values[] = {0, 1, 2};
  vector<int> v2b(v2b_values, end(&v2b_values));
  int v3_values[] = {0, 1, 10};
  vector<int> v3(v3_values, end(&v3_values));
  int v3b_values[] = {0, 1, 1};
  vector<int> v3b(v3b_values, end(&v3b_values));

  all_comparisons(v1, v1b);
  all_comparisons(v1, v2);
  all_comparisons(v1, v2b);
  all_comparisons(v1, v3);
  all_comparisons(v1, v3b);
}
