#ifndef CONN_MANG
#define CONN_MANG
#include "ClientSession.h"
#include "CommandExecutor.h"
#include <boost/asio.hpp>

class ConnectionManager {
public:
  explicit ConnectionManager(boost::asio::io_context &, short port);
  void listenAsync();
  void readAsync(ClientSession &ses);
  void writeAsync(ClientSession &ses, std::string response);

private:
  boost::asio::io_context &_io_context;
  boost::asio::ip::tcp::resolver _resolver;
  boost::asio::ip::tcp::acceptor _acceptor;

  void handleAccept(boost::asio::ip::tcp::socket socket);
};

#endif // ! CONN_MANG
