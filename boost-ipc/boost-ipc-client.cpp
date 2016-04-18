#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include "boost-ipc.h"

int main(int argc, char* argv []) {

  using namespace boost::interprocess;
  using namespace std;

  // Open the shared mem object
  shared_memory_object shm (open_only, "TestShm", read_write);

  // Map the memory into the process
  mapped_region region(shm, read_write);

  void* addr = region.get_address();

  shared_mem_buffer* data = static_cast<shared_mem_buffer*>(addr);

  // Run test client for N exchanges
  int count = 0;
  int N = stoi(argv[1]);
  while(count < N) {
    // Setup string to send
    string s = "Test string: " + to_string(count);
    ++count;

    // Populate shared mem struct
    data->len = s.size();
    strcpy(data->buf, s.c_str());

    if (count % 10000 == 0)
      cout << count << ": " << data->buf << endl;

    // Notify server of new data and wait for response
    data->server.post();
    data->client.wait();
    if (count % 10000 == 0)
      cout << count << ": " << data->buf << endl;
  }

  return 0;

}
