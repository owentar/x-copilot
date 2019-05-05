#include <algorithm>
#include <chrono>
#include <memory>
#include <thread>
#include <utility>

#include "CommandsConfigReader.h"
#include "Logger.h"
#include "Recognizer.h"
#ifdef IBM
#include "WinRecognizer.h"
#else
#include "UnixRecognizer.h"
#endif
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
#ifdef IBM
    std::unique_ptr<Recognizer> recognizer = std::make_unique<WinRecognizer>();
#else
    std::unique_ptr<Recognizer> recognizer = std::make_unique<UnixRecognizer>();
#endif
    XCopilot xcopilot(std::move(recognizer));

    xcopilot.enable();
    xcopilot.configureForAircraft(commands);

    std::vector<CommandExecutor> recognizedCommands;

    Logger::getInstance()->debug("Listening...");
    do
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        recognizedCommands = xcopilot.getPendingCommands();
    } while (recognizedCommands.empty());

    logger->info("Command recognized");

    xcopilot.disable();
    logger->info("We're done");

    return 0;
}
