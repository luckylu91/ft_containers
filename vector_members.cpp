#include "vector.hpp"
#include <iostream>
#include <iomanip>

int main()
{
	ft::vector<int> vect;

	// push_back, size, capacity
	std::cout << "vector default (size, capacity): (" << vect.size() << ", " << vect.capacity() << ")" << std::endl;
	for (int i = 0; i < 21; i++)
	{
		vect.push_back(i);
		std::cout << std::setw(4) << vect.size() << std::setw(4) << vect.capacity() << std::endl;
	}
}
