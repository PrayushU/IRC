#include "ConnectionManager.h"
#include "ClientSession.h"
#include "MessageParser.h"
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <string>

ConnectionManager::ConnectionManager(boost::asio::io_context &io_context,
                                     short port)
    : _io_context{io_context}, _resolver{io_context},
      _acceptor{io_context, boost::asio::ip::tcp::endpoint(
                                boost::asio::ip::tcp::v4(), port)} {}

void ConnectionManager::listenAsync() {
  _acceptor.async_accept([this](const boost::system::error_code &error,
                                boost::asio::ip::tcp::socket socket) {
    if (!error) {
      std::cout << "[INFO] Connection Accepted" << std::endl;
      std::cout << "[INFO] Created session on: "
                << socket.remote_endpoint().address().to_string() << " : "
                << socket.remote_endpoint().port() << std::endl;

      handleAccept(std::move(socket));

      listenAsync();
    } else {
      std::cout << "[Error] occured when accepting connection" << std::endl;
    }
  });
}

void ConnectionManager::handleAccept(boost::asio::ip::tcp::socket socket) {
  // Store the shared_ptr to keep the ClientSession alive
  auto session = std::make_shared<ClientSession>(std::move(socket));

  std::string response =
      "[INFO] Connected to server at: " +
      _acceptor.local_endpoint().address().to_string() +
      " | port: " + std::to_string(_acceptor.local_endpoint().port());
  writeAsync(*session, std::move(response));
  readAsync(*session);
}

void ConnectionManager::readAsync(ClientSession &ses) {
  boost::asio::async_read_until(
      ses.socket, ses.readBuffer, "\n",
      [this, &ses, self = ses.shared_from_this()](boost::system::error_code ec,
                                                  std::size_t length) {
        if (!ec) {
          // Extract data correctly from the streambuf
          std::istream is(&ses.readBuffer);
          std::string line;
          std::getline(is, line);

          IRCMessage message = MessageParser::parse(line);
          std::cout << "[DEBUG] " << ses.endpoint.address().to_string() << ","
                    << std::to_string(ses.endpoint.port()) << " | "
                    << message.toString() << std::endl;
          // std::cout << line << std::endl;

          // Continue reading (call readAsync again)
          ConnectionManager::readAsync(ses);
        } else {
          std::cout << "[Error]: " << ec.message() << std::endl;
        }
      });
}

void ConnectionManager::writeAsync(ClientSession &ses, std::string response) {
  auto buffer = std::make_shared<std::string>(response + "\n"); // Good: Using
  // shared_ptr for buffer

  boost::asio::async_write(
      ses.socket, boost::asio::buffer(*buffer),
      [&ses, buffer, self = ses.shared_from_this()](
          const boost::system::error_code ec, std::size_t bytes_transferred) {
        // Capture buffer to keep it alive
        // Capture session by reference if needed

        if (!ec) {
          // Write succeeded
          // You might want to do something here
        } else {
          // Handle error
          std::cerr << "[ERROR] Write error: " << ec.message() << std::endl;
        }
      });
}
