#include "test_speed.hpp"

int main(int argc, char** argv) {
	if (argc != 2)
	{
		// std::cerr << "Usage: ./test seed" << std::endl;
		// std::cerr << "Provide a seed please" << std::endl;
		std::cerr << COUNT;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

  clock_t begin = clock();

  test();

  clock_t end = clock();
  std::cout << std::setprecision(3) << double(end - begin) / CLOCKS_PER_SEC;

  return 0;
}
