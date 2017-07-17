#include "XCopilot.h"

#include "Recognizer.h"
#include "PocketsphinxWrapper.h"
#include "Microphone.h"

XCopilot* XCopilot::instance = nullptr;

XCopilot::XCopilot() : microphone{}, pocketsphinx{}, recognizer{&pocketsphinx, &microphone}
{
}

XCopilot* XCopilot::getInstance()
{
    if (!instance)
    {
        instance = new XCopilot();
    }

    return instance;
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
}
