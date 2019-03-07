#include <algorithm>
#include <memory>
#include <utility>

#include "CommandsConfigReader.h"
#include "Logger.h"
#include "Microphone.h"
#include "PocketsphinxWrapper.h"
#include "Recognizer.h"
#include "XCopilot.h"
#include "XPlaneDataRefSDKStub.h"

using namespace xcopilot;

int main(int argc, char *argv[]) {
    Logger::configureFileLogger();
    Logger::configureConsoleLogger(Logger::Level::DEBUG);
    Logger* logger = Logger::getInstance();
    logger->info("Starting demo");

    XPlaneDataRefSDKStub xplaneSDK;
    CommandsConfigReader commandsConfigReader(&xplaneSDK);
    auto commands = commandsConfigReader.getCommandsFromFile();
    std::unique_ptr<Microphone> microphone = std::make_unique<Microphone>();
    std::unique_ptr<Pocketsphinx> pocketsphinx = std::make_unique<Pocketsphinx>();
    std::unique_ptr<Recognizer> recognizer = std::make_unique<Recognizer>(std::move(pocketsphinx), std::move(microphone));
    XCopilot xcopilot(std::move(recognizer));

    xcopilot.enable();
    xcopilot.configureForAircraft(commands);

    Logger::getInstance()->debug("Listening...");
    while(!xcopilot.hasPendingCommands()) {}

    xcopilot.executePendingCommands();
    xcopilot.disable();

    return 0;
}
