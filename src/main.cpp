#include "test.h"

int main()
{
  try {
    test();
  }
  catch (std::exception & e) {
    std::cerr << e.what() << std::endl;
  }
}
