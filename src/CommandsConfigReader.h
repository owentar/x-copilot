#ifndef X_COPILOT_COMMANDSREADER_H
#define X_COPILOT_COMMANDSREADER_H

#include <memory>
#include <regex>
#include <string>
#include <vector>

#include "CommandRecognizer.h"
#include "XPlaneDataRefSDK.h"

#define DEFAULT_INDEX_FILE_PATH "config/commands-index.json"
#define DEFAULT_COMMANDS_FILE_PATH "config/default-commands.json"

namespace xcopilot {
    struct AircraftCommandsMatcher {
        std::string id;
        std::string author;
        std::string icao;
        std::string description;
        std::string commandsFilePath;

        bool match(const std::string author, const std::string icao, const std::string desc) {
            std::regex authorRegex(this->author, std::regex_constants::icase);
            std::regex icaoRegex(this->icao, std::regex_constants::icase);
            std::regex descRegex(this->description, std::regex_constants::icase);
            return std::regex_match(author, authorRegex) && std::regex_match(icao, icaoRegex) &&
                   std::regex_match(desc, descRegex);
        }
    };

    class CommandsConfigReader {
    public:
        explicit CommandsConfigReader(xcopilot::XPlaneDataRefSDK *xPlaneSDK) : xPlaneSDK{xPlaneSDK} {};

        virtual std::vector<xcopilot::AircraftCommandsMatcher>
        getAircraftCommandsMatchers(const std::string& indexFilePath = DEFAULT_INDEX_FILE_PATH);

        virtual std::vector<std::shared_ptr<xcopilot::CommandRecognizer>>
        getCommandsFromFile(const std::string& commandsFilePath = DEFAULT_COMMANDS_FILE_PATH);

        virtual ~CommandsConfigReader() = default;

    protected:
        explicit CommandsConfigReader() : xPlaneSDK{nullptr} {};

    private:
        xcopilot::XPlaneDataRefSDK *xPlaneSDK;
    };
}

#endif //X_COPILOT_COMMANDSREADER_H
