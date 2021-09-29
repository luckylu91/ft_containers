#include "test_speed.hpp"

void test() {
  vector<Buffer> vector_buffer;
  for (int i = 0; i < COUNT; i++) {
    vector_buffer.push_back(Buffer());
  }
  for (int i = 0; i < COUNT; i++)
  {
    const int idx = rand() % COUNT;
    vector_buffer[idx].idx = 5;
  }
  vector<Buffer>().swap(vector_buffer);
}
