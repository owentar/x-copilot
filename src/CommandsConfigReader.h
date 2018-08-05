#ifndef X_COPILOT_COMMANDSREADER_H
#define X_COPILOT_COMMANDSREADER_H

#include <memory>
#include <vector>

#include "CommandRecognizer.h"
#include "XPlaneDataRefSDK.h"

#define DEFAULT_COMMANDS_FILE_PATH "config/default-commands.json"

namespace xcopilot {
    class CommandsConfigReader {
    public:
        CommandsConfigReader(XPlaneDataRefSDK* xPlaneSDK) : xPlaneSDK{xPlaneSDK} {};

        std::vector<std::shared_ptr<CommandRecognizer>> getCommandsForAircraft(const std::string configFilePath = DEFAULT_COMMANDS_FILE_PATH);

        std::vector<std::shared_ptr<CommandRecognizer>> getCommandsForAircraft(const std::string author, const std::string icao, const std::string desc, const std::string configFilePath = DEFAULT_COMMANDS_FILE_PATH);

    private:
        XPlaneDataRefSDK* xPlaneSDK;
    };
}

#endif //X_COPILOT_COMMANDSREADER_H
