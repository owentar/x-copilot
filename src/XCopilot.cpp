#include "XCopilot.h"

#include <regex>
#include <algorithm>

#include "Recognizer.h"
#include "PocketsphinxWrapper.h"
#include "Microphone.h"
#include "Command.h"

XCopilot* XCopilot::instance = nullptr;

XCopilot::XCopilot() : microphone{}, pocketsphinx{}, recognizer{&pocketsphinx, &microphone}, commands{}, commandProcessor{}
{
    //commandProcessor.push_back(std::regex{"^set altimeter ((zero|one|two|three|four|five|six|seven|eight|nine)\\s?){4}$"});
}

XCopilot* XCopilot::getInstance()
{
    if (!instance)
    {
        instance = new XCopilot();
    }

    return instance;
}

void XCopilot::releaseInstance()
{
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}

void XCopilot::enable()
{
    recognizer.start();
}

void XCopilot::disable()
{
    recognizer.stop();
}

void XCopilot::configureForAircraft(const char* author, const char* description, const char* icao)
{
    recognizer.connect([this] (const std::string& phrase) { recognizeCommand(phrase); });
}

void XCopilot::recognizeCommand(const std::string& phrase)
{
    auto value = std::find_if(commandProcessor.begin(), commandProcessor.end(),
                              [phrase] (const Command* command) -> bool { return command->isRecognized(phrase); });
    if (value != commandProcessor.end()) {
        commands.push(1);
    }
}
