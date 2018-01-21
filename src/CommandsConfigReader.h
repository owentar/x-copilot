#ifndef X_COPILOT_COMMANDSREADER_H
#define X_COPILOT_COMMANDSREADER_H

#include <memory>
#include <vector>

#include "Command.h"
#include "XPlaneDataRefSDK.h"

namespace xcopilot {
    class CommandsConfigReader {
    public:
        CommandsConfigReader(XPlaneDataRefSDK* xPlaneSDK) : xPlaneSDK{xPlaneSDK} {};

        std::vector<std::shared_ptr<Command>> getCommandsForAircraft();

    private:
        XPlaneDataRefSDK* xPlaneSDK;
    };
}

#endif //X_COPILOT_COMMANDSREADER_H
