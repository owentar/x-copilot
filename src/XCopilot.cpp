#include "XCopilot.h"

#include "Recognizer.h"
#include "CommandRecognizer.h"

using namespace xcopilot;

void XCopilot::configureForAircraft(const std::vector<std::shared_ptr<CommandRecognizer>>& commands)
{
    recognizer->configure(std::move(commands));
}
