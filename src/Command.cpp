#include <iostream>
#include "Command.h"

#include "IntCommandExecutor.h"

bool Command::isRecognized(const std::string& phrase) const
{
    bool result = std::regex_match(phrase, commandRegExp);
    std::cout << "Result: " << result <<" - Phrase: " << phrase << std::endl;
    return result;
}

CommandExecutorPtr Command::getExecutor(const std::string& phrase)
{
    std::smatch result;
    std::regex_search(phrase, result, commandRegExp);
    std::string altitude = result[1];
    return CommandExecutorPtr{new IntCommandExecutor(altitude, dataRefsIds)};
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