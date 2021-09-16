#include "test_vector.h"

void test()
{
	vector<int> vect;

	std::cout << "vector default (size, capacity): (" << vect.size() << ", " << vect.capacity() << ")" << std::endl;
	for (int i = 0; i < 21; i++)
	{
		vect.push_back(i);
		std::cout << std::setw(4) << vect.size() << std::setw(4) << vect.capacity() << std::endl;
	}
}
