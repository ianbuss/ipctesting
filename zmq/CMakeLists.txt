link_directories(/usr/local/Cellar/zmqpp/4.1.2/lib /usr/local/Cellar/zeromq/4.1.2/lib)

set(ZMQ_SV zmq-server.cpp)
set(ZMQ_CL zmq-client.cpp)

add_executable(zmq-server ${ZMQ_SV})
add_executable(zmq-client ${ZMQ_CL})

target_link_libraries(zmq-server zmq zmqpp)
target_link_libraries(zmq-client zmq zmqpp)
