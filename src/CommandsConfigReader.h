#ifndef X_COPILOT_COMMANDSREADER_H
#define X_COPILOT_COMMANDSREADER_H

#include <memory>
#include <string>
#include <vector>

#include "Command.h"
#include "XPlaneDataRefSDK.h"

namespace xcopilot {
    class __declspec(dllexport) CommandsConfigReader {
    public:
        CommandsConfigReader(XPlaneDataRefSDK* xPlaneSDK) : xPlaneSDK{xPlaneSDK} {};

        std::vector<std::shared_ptr<Command>> getCommandsForAircraft(const std::string author, const std::string icao, const std::string desc);

    private:
        XPlaneDataRefSDK* xPlaneSDK;
    };
}

#endif //X_COPILOT_COMMANDSREADER_H
