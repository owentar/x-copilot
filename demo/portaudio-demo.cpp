#include <memory>
#include <utility>

#include "Command.h"
#include "Microphone.h"
#include "PocketsphinxWrapper.h"
#include "Recognizer.h"
#include "XCopilot.h"
#include "XPlaneDataRefSDKStub.h"

#include <iostream>

int main(int argc, char *argv[]) {
    XPlaneDataRefSDKStub xplaneSDK;
    Microphone microphone;
    Pocketsphinx pocketsphinx;
    std::unique_ptr<Recognizer> recognizer = std::make_unique<Recognizer>(&pocketsphinx, &microphone);
    XCopilot xcopilot(std::move(recognizer));
    Command command("Test Command", "^set altitude ((?:(?:\\\\d|zero|one|two|three|four|five|six|seven|eight|nine)\\\\s?){3,5})$", "set/altitude", &xplaneSDK);
    xcopilot.addCommand(&command);

    xcopilot.enable();
    xcopilot.configureForAircraft("", "", "");

    std::cout << "Listening..." << std::endl;
    while(!xcopilot.hasCommands()) {}

    xcopilot.executePendingCommands();
    xcopilot.disable();

    return 0;
}
