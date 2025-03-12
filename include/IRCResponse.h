#ifndef RESPONSE
#define RESPONSE

#include <string>
#include <vector>
#include <sstream>

enum class IRCReply {

};

struct IRCResponse {
  IRCReply code;
  std::vector<std::string> parameters;
  std::string sender;
  std::string receiver;
  std::string message;
 
  std::string toString(){
    std::ostringstream oss;
    oss << ":" << sender << static_cast<int>(code) << " " << receiver; 
    for (const auto& param: parameters){
      oss << " " << param;
    }

    oss << " :" << message;
    return oss.str();
  }


};

#endif // !RESPONSE
