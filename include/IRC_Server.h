#ifndef IRC_SERV
#define IRC_SERV

#include "ConnectionManager.h"
#include <boost/asio.hpp>
class IRC_Server{
public: 
  IRC_Server(boost::asio::io_context& context);
  void start();
private:
  boost::asio::io_context& _io_context;
  std::shared_ptr<ConnectionManager> _connection_manager;
};

#endif // IRC_SERV
