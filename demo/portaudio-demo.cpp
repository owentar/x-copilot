#include <iostream>
#include <memory>
#include <utility>

#include "Command.h"
#include "Microphone.h"
#include "PocketsphinxWrapper.h"
#include "Recognizer.h"
#include "XCopilot.h"
#include "XPlaneDataRefSDKStub.h"
#include "Logger.h"

using namespace xcopilot;

int main(int argc, char *argv[]) {
    Logger* logger = Logger::getInstance();
    logger->info("Initializing demo");

    XPlaneDataRefSDKStub xplaneSDK;
    std::unique_ptr<Microphone> microphone = std::make_unique<Microphone>();
    std::unique_ptr<Pocketsphinx> pocketsphinx = std::make_unique<Pocketsphinx>();
    std::unique_ptr<Recognizer> recognizer = std::make_unique<Recognizer>(std::move(pocketsphinx), std::move(microphone));
    XCopilot xcopilot(std::move(recognizer));
    Command command1("SET ALTITUDE", "^set altitude ((?:(?:\\d|zero|one|two|three|four|five|six|seven|eight|nine)\\s?){3,5})$", {"set/altitude"}, &xplaneSDK);
    Command command2("SET ALTIMETER", "^set altimeter ((?:(?:\\d|zero|one|two|three|four|five|six|seven|eight|nine)\\s?){4})", {"set/altimeter"}, &xplaneSDK);
    xcopilot.addCommand(&command1);
    xcopilot.addCommand(&command2);

    xcopilot.enable();
    xcopilot.configureForAircraft("", "", "");

    std::cout << "Listening..." << std::endl;
    while(!xcopilot.hasCommands()) {}

    xcopilot.executePendingCommands();
    xcopilot.disable();

    return 0;
}
