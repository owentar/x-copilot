#include "XCopilot.h"

#include <algorithm>
#include <regex>
#include <boost/format.hpp>

#include "Logger.h"
#include "Recognizer.h"
#include "Command.h"

using namespace xcopilot;
using boost::format;

void XCopilot::configureForAircraft(const std::vector<std::shared_ptr<Command>>& commands)
{
	recognizer->configure(std::move(commands));
}

std::vector<CommandExecutor> XCopilot::getPendingCommands()
{
	return recognizer->getRecognizedCommands();
}
