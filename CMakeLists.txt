cmake_minimum_required(VERSION 3.0)
project(ipctesting)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated-declarations")

add_subdirectory(boost-ipc)
add_subdirectory(zmq)
