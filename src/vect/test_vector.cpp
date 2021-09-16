#include "test_vector.h"

template <class Iterator>
void iter(Iterator begin, Iterator end, void (*f)(typename Iterator::value_type&)) {
  for (Iterator it = begin; it != end; ++it) {
    f(*it);
  }
}

template <class T>
void printElem(T &elem) {
  std::cout << elem << " ";
}

void test() {
	vector<int> vect(6, 1);
  vect.push_back(0);
  vect.push_back(1);
  vect[2] = 2;
  std::cout << "size = " << vect.size() << std::endl;
  std::cout << "capacity = " << vect.capacity() << std::endl;
	try
	{
		vect.at(10);
	}
	catch (std::exception const & e)
	{
		std::cout << e.what() << std::endl;
	}

  vector<int> vectIter(vect.begin(), vect.end() - 1);
  iter(vect.begin(), vect.end(), printElem);
  std::cout << std::endl;
  iter(vectIter.begin(), vectIter.end(), printElem);
  std::cout << std::endl;
}
