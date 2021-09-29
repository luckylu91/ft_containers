#include "test_speed.hpp"

void test() {
  vector<Buffer> vector_buffer;
  for (int i = 0; i < 100000; i++) {
    vector_buffer.push_back(Buffer());
  }
  for (int i = 0; i < 100000; i++)
  {
    const int idx = rand() % 100000;
    vector_buffer[idx].idx = 5;
  }
}
