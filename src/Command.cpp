#include "Command.h"

#include <iostream>

#include "CommandExecutor.h"

using namespace xcopilot;

bool Command::isRecognized(const std::string& phrase) const
{
    bool result = std::regex_match(phrase, commandRegExp);
    std::cout << "Result: " << result <<" - Phrase: " << phrase << std::endl;
    return result;
}

CommandExecutor Command::getExecutor(const std::string& phrase)
{
    std::smatch result;
    std::regex_search(phrase, result, commandRegExp);
    std::string value = result[1];
    return CommandExecutor{value, dataRefsIds, CommandType::INT};
}

//void Command::execute(const std::string& phrase) const
//{
//    std::smatch result;
//    std::regex_search(phrase, result, commandRegExp);
//    std::string altitude = result[1];
//    auto value = parseToInt(altitude);
//    xPlaneDataRefSDK->setValue(dataRefId, value);
//}

//double Command::getValue(const std::string& phrase) const
//{
//    std::smatch result;
//    std::regex_search(phrase, result, commandRegExp);
//    std::string altitude = result[1];
//    return parseToDecimal(altitude, 2);
//}