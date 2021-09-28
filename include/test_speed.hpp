#pragma once
#include <iostream>
#include <string>
#include <deque>
#include <iomanip>
#ifdef MINE
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
	using namespace ft;
#else
	#include <map>
	#include <stack>
	#include <vector>
	using namespace std;
#endif

#include <cstdlib>
#include <ctime>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096

struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

void test();
