#ifndef X_COPILOT_COMMANDSREADER_H
#define X_COPILOT_COMMANDSREADER_H

#include <vector>

#include "Command.h"
#include "XPlaneDataRefSDK.h"

namespace xcopilot {
    class CommandsConfigReader {
    public:
        CommandsConfigReader(XPlaneDataRefSDK* xPlaneSDK) : xPlaneSDK{xPlaneSDK} {};

        std::vector<Command> getCommandsForAircraft();

    private:
        XPlaneDataRefSDK* xPlaneSDK;
    };
}

#endif //X_COPILOT_COMMANDSREADER_H
