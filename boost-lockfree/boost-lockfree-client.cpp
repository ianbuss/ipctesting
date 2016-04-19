#include <iostream>
#include <string>
#include "boost-lockfree.h"

int main(int argc, char* argv[]) {
    using namespace boost::interprocess;

    // Args
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " NUM\n";
        return -1;
    }

    managed_shared_memory rx_segment(open_only, "SharedServerRx");
    managed_shared_memory tx_segment(open_only, "SharedServerTx");
    
    shm::char_alloc rx_allocator(rx_segment.get_segment_manager());
    shm::char_alloc tx_allocator(tx_segment.get_segment_manager());
    shm::ring_buffer *rx_queue = rx_segment.find_or_construct<shm::ring_buffer>("rxQueue")();
    shm::ring_buffer *tx_queue = tx_segment.find_or_construct<shm::ring_buffer>("txQueue")();

    // Run test client for N exchanges
    int count = 0;
    int N = std::stoi(argv[1]);
    while(count < N) {
        ++count;
        
        std::string s { "Test string" + std::to_string(count) };
        shm::shared_string rx_val(s.c_str(), rx_allocator);
        shm::shared_string tx_val(tx_allocator);

        rx_queue->push(rx_val);
        while (!tx_queue->pop(tx_val)) {
            ;
        }
        if (count % 10000 == 0)
            std::cout << count << ": " << tx_val << std::endl;
    }
}