include_directories(SYSTEM /usr/local/Cellar/boost/1.60.0_1/include)

set(SERVER boost-lockfree-server.cpp)
set(CLIENT boost-lockfree-client.cpp)

add_executable(boost-lockfree-server ${SERVER})
add_executable(boost-lockfree-client ${CLIENT})

