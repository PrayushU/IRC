#ifndef MESG_PARSER
#define MESG_PARSER
#include <string>
#include <vector>

struct IRCMessage {
  std::string message; //Full message

  std::string prefix;
  std::string command;
  std::vector<std::string> parameters;
  bool has_trailing = false;

  // Convert the message back to a complete IRC message string
  std::string toString() const {
    std::string result;

    // Estimate the size to avoid reallocations
    size_t estimated_size =
        (prefix.empty() ? 0 : prefix.length() + 2) + // +2 for ":" and space
        command.length() + 1; // +1 for space after command

    // Add estimated size for parameters
    for (const auto &param : parameters) {
      estimated_size += param.length() + 1; // +1 for space
    }

    // Add trailing parameter colon and final newline
    if (has_trailing) {
      estimated_size += 1; // +1 for the colon
    }
    estimated_size += 1; // +1 for the final newline

    result.reserve(estimated_size);

    // Add prefix if it exists
    if (!prefix.empty()) {
      result += ':';
      result += prefix;
      result += ' ';
    }

    // Add command
    result += command;

    // Add regular parameters
    size_t param_count = parameters.size();
    size_t last_param = has_trailing ? param_count - 1 : param_count;

    for (size_t i = 0; i < last_param; i++) {
      result += ' ';
      result += parameters[i];
    }

    // Add trailing parameter if it exists
    if (has_trailing && param_count > 0) {
      result += " :";
      result += parameters.back();
    }

    // Add final newline (IRC messages typically end with \r\n but we'll use \n
    // for simplicity) result += '\n';

    return result;
  }
};

class MessageParser {

public:
  static IRCMessage parse(const std::string &message);
};
#endif // !MESG_PARSER
