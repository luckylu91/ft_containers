#include <vector>
#include <iostream>
#include <exception>

using namespace std;

int main()
{
	vector<int> vect(1);
	try
	{
		vect.at(10);
	}
	catch (std::exception const & e)
	{
		std::cout << e.what() << std::endl;
	}
}
