#include "XCopilot.h"

#include <regex>
#include <algorithm>

#include "Recognizer.h"
#include "PocketsphinxWrapper.h"
#include "Microphone.h"
#include "Command.h"

#include <iostream>

void XCopilot::configureForAircraft(const char* author, const char* description, const char* icao)
{
    recognizer->connect([this] (const std::string& phrase) { recognizeCommand(phrase); });
}

void XCopilot::recognizeCommand(const std::string& phrase)
{
    std::cout << "Processing: " << phrase << std::endl;
    auto value = std::find_if(commandProcessor.begin(), commandProcessor.end(),
                              [phrase] (const Command* command) -> bool { return command->isRecognized(phrase); });
    if (value != commandProcessor.end()) {
        std::cout << "Command recognized: " << (*value) << std::endl;
        commands.push_back((*value)->getExecutor(phrase));
    }
}

void XCopilot::executePendingCommands()
{
    std::for_each(commands.begin(), commands.end(), [](const CommandExecutor& commandExecutor) { commandExecutor.execute(); });
    commands.clear();
}
