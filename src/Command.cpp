#include "Command.h"

#include <boost/format.hpp>

#include "Logger.h"
#include "CommandExecutor.h"

using namespace xcopilot;
using boost::format;

bool Command::isRecognized(const std::string& phrase) const
{
    bool result = std::regex_match(phrase, commandRegExp);
    Logger::getInstance()->debug(format("Result: %1% - Phrase: %2%") % result % phrase);
    return result;
}

CommandExecutor Command::getExecutor(const std::string& phrase)
{
    std::smatch result;
    std::regex_search(phrase, result, commandRegExp);
    std::string value = result[1];
    return CommandExecutor{value, dataRefsIds, CommandType::INT};
}
