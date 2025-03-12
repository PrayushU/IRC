#include "MessageParser.h"
#include "IRCResponse.h"



class CommandExecutor{
private:
  IRCResponse handlePONG();


public:
  IRCResponse execute(const IRCMessage& message);
  
};
