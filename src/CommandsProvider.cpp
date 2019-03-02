#include "CommandsProvider.h"

#include <algorithm>
#include <numeric>
#include <optional>
#include <vector>

using namespace xcopilot;

std::optional<AircraftCommandsMatcher>
CommandsProvider::getAircraftCommandsMatcher(const std::string author, const std::string icao, const std::string desc) {
    auto matcher = std::find_if(aircraftCommandsMatchers.begin(), aircraftCommandsMatchers.end(),
                 [author, icao, desc](AircraftCommandsMatcher matcher) -> bool { return matcher.match(author, icao, desc); });
    if (matcher != aircraftCommandsMatchers.end()) {
        return (*matcher);
    }
    return std::nullopt;
}

std::vector<std::shared_ptr<CommandRecognizer>>
CommandsProvider::getCommandsForAircraft(const std::string author, const std::string icao, const std::string desc) {
    auto defaultCommands = commandsConfigReader->getCommandsFromFile();
    auto matcher = getAircraftCommandsMatcher(author, icao, desc);

    if (matcher) {
        auto aircraftCommands = commandsConfigReader->getCommandsFromFile(matcher->commandsFilePath);
        return std::accumulate(defaultCommands.begin(), defaultCommands.end(), aircraftCommands,
                [](std::vector<std::shared_ptr<CommandRecognizer>> commands, const std::shared_ptr<CommandRecognizer> defaultCommand) -> std::vector<std::shared_ptr<CommandRecognizer>> {
            if (std::none_of(commands.begin(), commands.end(),
                    [defaultCommand](const std::shared_ptr<CommandRecognizer> c) -> bool {
                        return c->getName() == defaultCommand->getName();
                    })) {
                commands.push_back(defaultCommand);
            }
            return commands;
        });
    }

    return defaultCommands;
}
