#ifndef X_COPILOT_COMMANDSREADER_H
#define X_COPILOT_COMMANDSREADER_H

#include <memory>
#include <vector>

#include "CommandRecognizer.h"
#include "XPlaneDataRefSDK.h"

namespace xcopilot {
    class CommandsConfigReader {
    public:
        CommandsConfigReader(XPlaneDataRefSDK* xPlaneSDK) : xPlaneSDK{xPlaneSDK} {};

        std::vector<std::shared_ptr<CommandRecognizer>> getCommandsForAircraft(const std::string configFilePath = "config/default-commands.json");

    private:
        XPlaneDataRefSDK* xPlaneSDK;
    };
}

#endif //X_COPILOT_COMMANDSREADER_H
