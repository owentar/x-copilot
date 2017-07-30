#include "Command.h"

#include <string>
#include <regex>

bool Command::isRecognized(const std::string& phrase) const
{
    return std::regex_match(phrase, commandRegExp);
}
