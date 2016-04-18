#include <zmqpp/zmqpp.hpp>
#include <string>
#include <iostream>

int main ()
{
  //  Prepare our context and socket
  zmqpp::context context;
  zmqpp::socket socket (context, zmqpp::socket_type::request);
  
  std::cout << "Connecting to hello world server..." << std::endl;
  socket.connect ("ipc:///tmp/zmq");
  for (int request_nbr = 0; request_nbr != 1000000; request_nbr++) {
    zmqpp::message request;
    request << "Hello";
    if (request_nbr % 100000 == 0)
      std::cout << "Sending Hello " << request_nbr << "..." << std::endl;
    socket.send (request);
  
    zmqpp::message reply;
    socket.receive (reply);
    if (request_nbr % 100000 == 0)
      std::cout << "Received World " << request_nbr << std::endl;
  }
  return 0;
}

