#include "test_reverse_iterator.hpp"

struct A {
  std::string s;
  A() : s("A") {}
  A(std::string const & s): s(s) {}
  A(A const & a) : s(a.s) {}
  A & operator=(A const & a) { s = a.s; return *this; }
  ~A() {}
};

void test() {
  std::boolalpha(std::cout);

  {
    typedef std::vector<int>::iterator vect_iterator;

    std::vector<int> vect;
    for (int i = 0; i < 10; ++i)
      vect.push_back(i);

    reverse_iterator<vect_iterator> rit_empty;
    reverse_iterator<vect_iterator> rit_end(vect.begin());
    reverse_iterator<vect_iterator> rit_begin(vect.end());

    for (reverse_iterator<vect_iterator> rit = rit_begin; rit != rit_end; ++rit) {
      if (rit != rit_begin)
        std::cout << ", ";
      std::cout << *rit;
    }
    std::cout << std::endl;

    reverse_iterator<vect_iterator> rit_3(rit_begin + 3);
    std::cout << "rit_3 = " << *rit_3 << std::endl;
    std::cout << "rit_3 - 2 = " << *(rit_3 - 2) << std::endl;
    std::cout << "rit_3-- = " << *(rit_3--) << std::endl;
    std::cout << "rit_3++ = " << *(rit_3++) << std::endl;
    std::cout << "--rit_3 = " << *(--rit_3) << std::endl;
    std::cout << "++rit_3 = " << *(++rit_3) << std::endl;
    std::cout << "rit_3 -= 2" << *(rit_3 -= 2) << std::endl;
    std::cout << "rit_3 += 2" << *(rit_3 += 2) << std::endl;
    std::cout << "rit_3[2] = " << rit_3[2] << std::endl;
    std::cout << "rit_3[2] <- 10" << std::endl;
    rit_3[2] = 10;
    std::cout << "rit_3[2] = " << rit_3[2] << std::endl;
    std::cout << "(rit_begin + 3 == rit_begin + 3) : " << (rit_begin + 3 == rit_begin + 3) << std::endl;
    std::cout << "(rit_begin + 3 == rit_begin + 4) : " << (rit_begin + 3 == rit_begin + 4) << std::endl;
    std::cout << "(rit_begin + 3 != rit_begin + 3) : " << (rit_begin + 3 != rit_begin + 3) << std::endl;
    std::cout << "(rit_begin + 3 != rit_begin + 4) : " << (rit_begin + 3 != rit_begin + 4) << std::endl;
    std::cout << "(rit_begin + 3 < rit_begin + 3) : " << (rit_begin + 3 < rit_begin + 3) << std::endl;
    std::cout << "(rit_begin + 3 < rit_begin + 4) : " << (rit_begin + 3 < rit_begin + 4) << std::endl;
    std::cout << "(rit_begin + 4 < rit_begin + 3) : " << (rit_begin + 3 < rit_begin + 4) << std::endl;
    std::cout << "(rit_begin + 3 > rit_begin + 3) : " << (rit_begin + 3 > rit_begin + 3) << std::endl;
    std::cout << "(rit_begin + 3 > rit_begin + 4) : " << (rit_begin + 3 > rit_begin + 4) << std::endl;
    std::cout << "(rit_begin + 4 > rit_begin + 3) : " << (rit_begin + 3 > rit_begin + 4) << std::endl;
    std::cout << "(rit_begin + 3 <= rit_begin + 3) : " << (rit_begin + 3 <= rit_begin + 3) << std::endl;
    std::cout << "(rit_begin + 3 <= rit_begin + 4) : " << (rit_begin + 3 <= rit_begin + 4) << std::endl;
    std::cout << "(rit_begin + 4 <= rit_begin + 3) : " << (rit_begin + 3 <= rit_begin + 4) << std::endl;
    std::cout << "(rit_begin + 3 >= rit_begin + 3) : " << (rit_begin + 3 >= rit_begin + 3) << std::endl;
    std::cout << "(rit_begin + 3 >= rit_begin + 4) : " << (rit_begin + 3 >= rit_begin + 4) << std::endl;
    std::cout << "(rit_begin + 4 >= rit_begin + 3) : " << (rit_begin + 3 >= rit_begin + 4) << std::endl;

    std::cout << std::endl;
    std::cout << "rit_end - rit_begin : " << (rit_end - rit_begin) << std::endl;
  }

  std::cout << std::endl;

  {
    typedef std::vector<A>::iterator vect_iterator;

    std::vector<A> vectA;
    for (int i = 0; i < 10; ++i)
      vectA.push_back(A(std::to_string(i)));

    reverse_iterator<vect_iterator> rit_empty;
    reverse_iterator<vect_iterator> rit_end(vectA.begin());
    reverse_iterator<vect_iterator> rit_begin(vectA.end());
    for (reverse_iterator<vect_iterator> rit = rit_begin; rit != rit_end; ++rit) {
      if (rit != rit_begin)
        std::cout << ", ";
      std::cout << rit->s;
    }
  }
}
