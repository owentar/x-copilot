#include "Command.h"
#include "utils.h"

bool Command::isRecognized(const std::string& phrase) const
{
    return std::regex_match(phrase, commandRegExp);
}

int Command::getValue(const std::string& phrase) const
{
    std::smatch result;
    std::regex_search(phrase, result, commandRegExp);
    std::string altitude = result[1];
    return parseToInt(altitude);
}