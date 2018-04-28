#ifndef X_COPILOT_COMMANDMETADATA_H
#define X_COPILOT_COMMANDMETADATA_H

#include <regex>
#include <string>

#include "CommandType.h"

namespace xcopilot {
    class CommandMetadata {
    public:
        CommandMetadata(const std::string& name, const CommandType type, const std::string& regex, const std::vector<std::string> dataRefs)
                : name{name}, type{type}, regex{regex, std::regex::icase}, dataRefs{dataRefs} {};

        std::string getName() const { return name; };

        CommandType getType() const { return type; };

        std::regex getRegEx() const { return regex; };

        std::vector<std::string> getDataRefs() const { return dataRefs; };

    private:
        std::string name;
        CommandType type;
        std::regex regex;
        std::vector<std::string> dataRefs;
    };
}

#endif //X_COPILOT_COMMANDMETADATA_H
