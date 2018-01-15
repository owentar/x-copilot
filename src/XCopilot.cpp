#include "XCopilot.h"

#include <regex>
#include <algorithm>
#include <boost/format.hpp>

#include "Logger.h"
#include "Recognizer.h"
#include "PocketsphinxWrapper.h"
#include "Microphone.h"
#include "Command.h"

using namespace xcopilot;
using boost::format;

void XCopilot::configureForAircraft(const char* author, const char* description, const char* icao)
{
    recognizer->connect([this] (const std::string& phrase) { recognizeCommand(phrase); });
}

void XCopilot::recognizeCommand(const std::string& phrase)
{
    Logger::getInstance()->debug(format("Processing: %1%") % phrase);
    auto value = std::find_if(commandProcessor.begin(), commandProcessor.end(),
                              [phrase] (const Command* command) -> bool { return command->isRecognized(phrase); });
    if (value != commandProcessor.end()) {
        Logger::getInstance()->debug(format("Command recognized: %1%") % (*value)->getName());
        commands.push_back((*value)->getExecutor(phrase));
    }
}

void XCopilot::executePendingCommands()
{
    Logger::getInstance()->debug(format("Executing %1% pending commands") % commands.size());
    std::for_each(commands.begin(), commands.end(), [](const CommandExecutor& commandExecutor) { commandExecutor.execute(); });
    commands.clear();
}
