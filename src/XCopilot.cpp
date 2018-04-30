#include "XCopilot.h"

#include <algorithm>
#include <regex>
#include <boost/format.hpp>

#include "Logger.h"
#include "Recognizer.h"
#include "PocketsphinxWrapper.h"
#include "Microphone.h"
#include "CommandRecognizer.h"

using namespace xcopilot;
using boost::format;

void XCopilot::configureForAircraft(const std::vector<std::shared_ptr<CommandRecognizer>>& commands)
{
    commandProcessor = std::move(commands);
    recognizer->connect([this] (const std::string& phrase) { recognizeCommand(phrase); });
}

void XCopilot::recognizeCommand(const std::string& phrase)
{
    Logger::getInstance()->debug(format("Processing: %1%") % phrase);
    auto value = std::find_if(commandProcessor.begin(), commandProcessor.end(),
                              [phrase] (const std::shared_ptr<CommandRecognizer> command) -> bool { return command->commandRecognized(phrase); });
    if (value != commandProcessor.end()) {
        Logger::getInstance()->debug(format("CommandRecognizer recognized: %1%") % (*value)->getName());
        pendingCommands.push_back((*value)->getExecutor(phrase));
    }
}

void XCopilot::executePendingCommands()
{
    Logger::getInstance()->debug(format("Executing %1% pending commands") % pendingCommands.size());
    std::for_each(pendingCommands.begin(), pendingCommands.end(), [](const CommandExecutor& commandExecutor) { commandExecutor.execute(); });
    pendingCommands.clear();
}
