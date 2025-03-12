#include "IRC_Server.h"
#include "ConnectionManager.h"
#include <thread>
#include <iostream>


IRC_Server::IRC_Server(boost::asio::io_context& context) : _io_context(context){

  _connection_manager = std::make_shared<ConnectionManager>(_io_context, 9000);
}


void IRC_Server::start(){
    auto work = boost::asio::make_work_guard(_io_context);

    _connection_manager->listenAsync();
    // This can be multithreaded
    std::thread th([this]() {
      try {
      std::cout << "[INFO] Started event loop" << std::endl;
        _io_context.run();
      } catch (const std::exception &exp) {
      std::cout << "[INFO] Event loop stopped" << std::endl;
      }
    });
  std::cout << "[INFO] Press enter to stop the app" << std::endl;
    std::cin.get();
  std::cout << "[INFO] Shutting down" << std::endl;
     
    work.reset();
    _io_context.stop();

    th.join();
}
