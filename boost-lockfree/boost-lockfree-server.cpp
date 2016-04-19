#include <iostream>
#include <string>
#include "boost-lockfree.h"

using namespace boost::interprocess;
using namespace std;

int main(int argc, char* argv[]) {
    struct shm_remove {
        shm_remove() { 
            shared_memory_object::remove("SharedServerRx");
            shared_memory_object::remove("SharedServerTx"); 
        }
        ~shm_remove() { 
            shared_memory_object::remove("SharedServerRx");
            shared_memory_object::remove("SharedServerTx"); 
        }
    } remover;

    // create the managed shared memory segment
    managed_shared_memory rx_segment(open_or_create, "SharedServerRx", 65536);
    managed_shared_memory tx_segment(open_or_create, "SharedServerTx", 65536);
    
    shm::char_alloc rx_allocator(rx_segment.get_segment_manager());
    shm::char_alloc tx_allocator(tx_segment.get_segment_manager());
    shm::ring_buffer *rx_queue = rx_segment.find_or_construct<shm::ring_buffer>("rxQueue")();
    shm::ring_buffer *tx_queue = tx_segment.find_or_construct<shm::ring_buffer>("txQueue")();

    int count = 0;
    while(true) {
        shm::shared_string rx_val(rx_allocator);
        
        while (!rx_queue->pop(rx_val)) {
            ;
        }
        ++count;
        if (count % 10000 == 0)
            cout << count << ": " << rx_val << endl;
        std::string s { rx_val.begin(), rx_val.end() };
        s += " : S" + to_string(count);
        shm::shared_string tx_val(s.c_str(), tx_allocator);
        tx_queue->push(tx_val);
    }
}