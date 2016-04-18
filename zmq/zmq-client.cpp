#include <zmqpp/zmqpp.hpp>
#include <string>
#include <iostream>

using namespace std;

int main (int argc, char* argv[])
{
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " NUM\n";
    return -1;
  }
  int N = stoi(argv[1]);
  // Prepare our context and socket
  zmqpp::context context;
  zmqpp::socket socket (context, zmqpp::socket_type::request);
  
  cout << "Connecting to hello world server..." << endl;
  socket.connect ("ipc:///tmp/zmq");
  for (int request_nbr = 1; request_nbr <= N; ++request_nbr) {
    zmqpp::message request;
    request << "Hello";
    if (request_nbr % 100000 == 0)
      cout << "Sending Hello " << request_nbr << "..." << endl;
    socket.send (request);
  
    zmqpp::message reply;
    socket.receive (reply);
    if (request_nbr % 100000 == 0)
      cout << "Received World " << request_nbr << endl;
  }
  return 0;
}

