#ifndef BOOSTLF_DEFINE_H
#define BOOSTLF_DEFINE_H

#include <boost/lockfree/spsc_queue.hpp> // ring buffer
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>

using namespace boost::interprocess;

namespace shm
{
    typedef allocator<char, managed_shared_memory::segment_manager> char_alloc;
    typedef basic_string<char, std::char_traits<char>, char_alloc > shared_string;

    typedef boost::lockfree::spsc_queue<
        shared_string, 
        boost::lockfree::capacity<200> 
    > ring_buffer;
}

#endif
