#include "test_speed.hpp"

int main() {
	// if (argc != 2)
	// {
	// 	std::cerr << "Usage: ./test seed" << std::endl;
	// 	std::cerr << "Provide a seed please" << std::endl;
	// 	std::cerr << COUNT;
	// 	return 1;
	// }
	// const int seed = atoi(argv[1]);
	srand(time(NULL));

  clock_t begin = clock();

  test();

  clock_t end = clock();
  std::cout << std::fixed;
  std::cout << std::setprecision(3);
  std::cout << double(end - begin) / CLOCKS_PER_SEC;

  return 0;
}
