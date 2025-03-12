#include "MessageParser.h"

IRCMessage MessageParser::parse(const std::string &message) {
  IRCMessage result;

  size_t i = 0;
  const size_t len = message.length();

  // Check for prefix (starts with ':')
  if (i < len && message[i] == ':') {
    i++; // Skip the initial ':'
    size_t prefixStart = i;

    // Collect prefix until space
    while (i < len && message[i] != ' ' && message[i] != '\n') {
      i++;
    }

    result.prefix = message.substr(prefixStart, i - prefixStart);

    // Skip whitespace after prefix
    if (i < len && message[i] == ' ') {
      i++;
    }
  }

  // Extract command
  size_t commandStart = i;
  while (i < len && message[i] != ' ' && message[i] != '\n') {
    i++;
  }

  result.command = message.substr(commandStart, i - commandStart);

  // Skip whitespace after command
  if (i < len && message[i] == ' ') {
    i++;
  }

  // Extract parameters
  while (i < len && message[i] != '\n') {
    // Handle trailing parameter (starts with ':')
    if (message[i] == ':') {
      i++; // Skip the ':'
      result.has_trailing = true;
      result.parameters.push_back(message.substr(i, len - i));
      // Trailing parameter consumes the rest of the line
      break;
    }

    // Skip multiple spaces between parameters
    if (message[i] == ' ') {
      i++;
      continue;
    }

    // Regular parameter
    size_t paramStart = i;
    while (i < len && message[i] != ' ' && message[i] != '\n') {
      i++;
    }

    result.parameters.push_back(message.substr(paramStart, i - paramStart));

    // Skip trailing space
    if (i < len && message[i] == ' ') {
      i++;
    }
  }

  return result;
}
