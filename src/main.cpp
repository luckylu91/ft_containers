#include <exception>
#include <iostream>

void test();

int main()
{
  try {
    test();
  }
  catch (std::exception & e) {
    std::cerr << e.what() << std::endl;
  }
}
