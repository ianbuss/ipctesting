include_directories(SYSTEM /usr/local/Cellar/boost/1.60.0_1/include)

set(SERVER boost-shm-manual-server.cpp)
set(CLIENT boost-shm-manual-client.cpp)

add_executable(boost-shm-manual-server ${SERVER})
add_executable(boost-shm-manual-client ${CLIENT})

