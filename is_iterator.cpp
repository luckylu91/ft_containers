#include "vector.hpp"
#include <vector>
#include <iterator>

int main()
{
  std::cout << ft::has_iterator_category< ft::vector<int>::iterator >::value << std::endl;
  std::cout << ft::has_iterator_category< ft::vector<int> >::value << std::endl;
  std::cout << ft::has_iterator_category< int >::value << std::endl;
  std::cout << ft::has_iterator_trait< ft::vector<int>::iterator, std::input_iterator_tag >::value << std::endl;
  std::cout << ft::has_iterator_trait< ft::vector<int>::iterator, std::random_access_iterator_tag >::value << std::endl;

  std::cout << ft::is_iterator<ft::vector<int>::iterator >::value << std::endl;
}
