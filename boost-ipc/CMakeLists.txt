include_directories(SYSTEM /usr/local/Cellar/boost/1.60.0_1/include)

set(SERVER boost-ipc-server.cpp)
set(CLIENT boost-ipc-client.cpp)

add_executable(boost-ipc-server ${SERVER})
add_executable(boost-ipc-client ${CLIENT})

