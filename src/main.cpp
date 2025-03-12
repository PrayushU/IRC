#include <boost/asio.hpp>
#include "IRC_Server.h"

int main(int argc, char *argv[]) {
  boost::asio::io_context context;
  
  IRC_Server server = IRC_Server(context);
  server.start();
  return 0;
}
