#ifndef SESSION
#define SESSION
#include <boost/asio.hpp>
#include <cstddef>
#include <iostream>
#include <istream>
#include <memory>
#include <utility>

class ClientSession : public std::enable_shared_from_this<ClientSession> {
public: // Make constructor public
  ClientSession(boost::asio::ip::tcp::socket soc) : socket{std::move(soc)}, endpoint{socket.remote_endpoint()}{
    // std::cout << "[DEBIG] remote endpoint: " << _socket.remote_endpoint().address().to_string() << std::endl;
  }
  
  boost::asio::streambuf readBuffer;
  boost::asio::ip::tcp::socket socket;
  boost::asio::ip::tcp::endpoint endpoint;
};

;
#endif
