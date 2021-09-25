#pragma once

#ifdef MINE
  #include "reverse_iterator.hpp"
  using namespace ft;
#else
  #include <iterator>
  using namespace std;
#endif

#include <iostream>
#include <iomanip>
#include <exception>
#include <vector>

void test();
