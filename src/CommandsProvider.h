#ifndef X_COPILOT_COMMANDSPROVIDER_H
#define X_COPILOT_COMMANDSPROVIDER_H

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "CommandsConfigReader.h"
#include "CommandRecognizer.h"

namespace xcopilot {
    class CommandsProvider {
    public:
        explicit CommandsProvider(xcopilot::XPlaneDataRefSDK* xPlaneSDK) : commandsConfigReader{std::make_unique<xcopilot::CommandsConfigReader>(xPlaneSDK)} { onInit(); };

        explicit CommandsProvider(std::unique_ptr<xcopilot::CommandsConfigReader> commandsConfigReader) : commandsConfigReader{std::move(commandsConfigReader)} { onInit(); };

        virtual std::vector<std::shared_ptr<xcopilot::CommandRecognizer>> getCommandsForAircraft(const std::string author, const std::string icao, const std::string desc);

        virtual ~CommandsProvider() = default;

    private:
        std::vector<xcopilot::AircraftCommandsMatcher> aircraftCommandsMatchers;
        std::unique_ptr<xcopilot::CommandsConfigReader> commandsConfigReader;

        void onInit() { aircraftCommandsMatchers = commandsConfigReader->getAircraftCommandsMatchers(); }
        std::optional<xcopilot::AircraftCommandsMatcher> getAircraftCommandsMatcher(const std::string, const std::string, const std::string);
    };
}


#endif //X_COPILOT_COMMANDSPROVIDER_H
