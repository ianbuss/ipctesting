#include <zmqpp/zmqpp.hpp>
#include <string>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)    Sleep(n)
#endif

int main () {
  //  Prepare our context and socket
  zmqpp::context context;
  zmqpp::socket socket (context, zmqpp::socket_type::reply);
  socket.bind ("ipc:///tmp/zmq");

  while (true) {
    zmqpp::message request;
  
    //  Wait for next request from client
    socket.receive (request);
    
    //  Send reply back to client
    zmqpp::message reply;
    reply << "World";
    socket.send(reply);
  }
  
  return 0;
}
