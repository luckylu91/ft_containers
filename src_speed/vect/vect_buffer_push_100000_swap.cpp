#include "test_speed.hpp"

void test() {
  vector<Buffer> vector_buffer;
  for (int i = 0; i < 100000; i++) {
    vector_buffer.push_back(Buffer());
  }
  vector<Buffer>().swap(vector_buffer);
}
