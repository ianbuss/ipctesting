#ifndef BOOSTSHMMAN_DEFINE_H
#define BOOSTSHMMAN_DEFINE_H

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace boost::interprocess;

struct shared_mem_buffer {
  shared_mem_buffer(): flag(0), len(0) {}
  int flag;
  char buf[32768];
  int len;
};

#endif
