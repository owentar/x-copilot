#ifdef IBM
#pragma warning(disable : 4996)
#endif

#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

#include "CommandsConfigReader.h"
#include "Logger.h"
#include "Recognizer.h"
#include "WinRecognizer.h"
#include "XPlaneDataRefSDKStub.h"

using namespace std;
using namespace xcopilot;

const int MY_REASONABLE_TIMEOUT = 5000;

int main(int argc, char *argv[]) {
	Logger::configureConsoleLogger(Logger::level::debug);
	Logger* logger = Logger::getInstance();
	XPlaneDataRefSDKStub xplaneSDK;
	CommandsConfigReader commandsConfigReader(&xplaneSDK);
	auto commands = commandsConfigReader.getCommandsForAircraft("", "", "");

	logger->info("Starting demo");
	std::unique_ptr<WinRecognizer> recognizer = std::make_unique<WinRecognizer>();
	recognizer->configure(commands);
	recognizer->start();
	logger->info("Listening...");

	std::vector<CommandExecutor> recognizedCommands;
	do
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		recognizedCommands = recognizer->getRecognizedCommands();
	} while (recognizedCommands.empty());

	logger->info("Command recognized");

	recognizer->stop();
	logger->info("We're done");
	return 0;
}
