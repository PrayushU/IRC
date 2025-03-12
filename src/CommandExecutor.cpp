#include "CommandExecutor.h"
#include "IRCResponse.h"
#include <iostream>


IRCResponse CommandExecutor::execute(const IRCMessage& message){
  if(message.command == "PONG"){
    return handlePONG();
  }
  //SHould not reach here. Command not found
  std::cerr << "[ERROR] Invalid command: " << message.message << std::endl;
  return IRCResponse{};
}


IRCResponse CommandExecutor::handlePONG(){
  
  std::cerr << "[DEBUG] PING Executed" << std::endl;
  return IRCResponse{};
}
