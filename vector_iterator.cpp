#include "vector.hpp"
#include <iostream>

int main()
{
	ft::vector<int> intVect;
	for (int i = 0; i < 10; i++)
		intVect.push_back(i);

	std::cout << "Mutable iterator" << std::endl;
	for (ft::vector<int>::iterator it = intVect.begin(); it != intVect.end(); ++it)
		std::cout << *it << ", ";
	std::cout << "END" << std::endl;

	std::cout << "Mutable reverse iterator" << std::endl;
	for (ft::vector<int>::reverse_iterator it = intVect.rbegin(); it != intVect.rend(); ++it)
		std::cout << *it << ", ";
	std::cout << "END" << std::endl;

	ft::vector<int> const cIntVect(intVect);

	std::cout << "Const iterator" << std::endl;
	for (ft::vector<int>::const_iterator it = cIntVect.begin(); it != cIntVect.end(); ++it)
		std::cout << *it << ", ";
	std::cout << "END" << std::endl;

	std::cout << "Reverse const iterator" << std::endl;
	for (ft::vector<int>::const_reverse_iterator it = cIntVect.rbegin(); it != cIntVect.rend(); ++it)
		std::cout << *it << ", ";
	std::cout << "END" << std::endl;
}
