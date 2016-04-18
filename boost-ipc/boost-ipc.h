#ifndef BOOSTIPC_DEFINE_H
#define BOOSTIPC_DEFINE_H

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

using namespace boost::interprocess;

struct shared_mem_buffer {
  shared_mem_buffer(): server(0), client(0), len(0) {}
  interprocess_semaphore server, client;
  char buf[32768];
  int len;
};

#endif
