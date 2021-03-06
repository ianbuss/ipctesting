#include <cstdlib>
#include <iostream>
#include <string>
#include "boost-shm-manual.h"

int main(int argc, char* argv []) {

  using namespace boost::interprocess;
  using namespace std;

  struct shm_remove {
    shm_remove() { shared_memory_object::remove("TestShmManual"); }
    ~shm_remove() { shared_memory_object::remove("TestShmManual"); }
  } remover;

  // Create the shared mem object
  shared_memory_object shm (create_only, "TestShmManual", read_write);
  shm.truncate(sizeof(shared_mem_buffer));

  // Map the memory into the process
  mapped_region region(shm, read_write);

  // Initialise all to 0
  memset(region.get_address(), 0, region.get_size());

  void* addr = region.get_address();

  shared_mem_buffer* data = new (addr) shared_mem_buffer;

  int count = 0;
  while(true) {
    // Wait for data from client
    while(data->flag == 0) {
      ;
    }
    ++count;

    // "Process" data
    string val { data->buf };
    val += ": S" + to_string(count);
    if (count % 10000 == 0)
      cout << count << ": " << val << endl;
    strcpy(data->buf, val.c_str());
    data->len = val.size();

    // Notify client of response
    data->flag = 0;
  }

  return 0;
}
