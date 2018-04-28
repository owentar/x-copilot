#include "Command.h"

#include <boost/format.hpp>

#include "Logger.h"
#include "CommandExecutor.h"

using namespace xcopilot;
using boost::format;

bool Command::isRecognized(const std::string& phrase) const
{
    bool result = std::regex_match(phrase, metadata.getRegEx());
    Logger::getInstance()->trace(format("Phrase: %1% - Result: %2%") % phrase % result);
    return result;
}

CommandExecutor Command::getExecutor(const std::string& phrase)
{
    std::smatch result;
    std::regex_search(phrase, result, metadata.getRegEx());
    std::string value = result[1];
    return CommandExecutor{value, metadata.getDataRefs(), metadata.getType()};
}
