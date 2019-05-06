#ifndef X_COPILOT_COMMANDMETADATA_H
#define X_COPILOT_COMMANDMETADATA_H

#include <regex>
#include <string>

#include "CommandType.h"
#include "XPLMDataAccess.h"

namespace xcopilot {
    class CommandMetadata {
    public:
        CommandMetadata(const int id, const std::string& name, const CommandType type, const std::string& regex, const std::vector<XPLMDataRef> dataRefs)
                : id{id}, name{name}, type{type}, regex{regex, std::regex::icase}, dataRefs{dataRefs} {};

        int getId() const { return id; }

        std::string getName() const { return name; };

        CommandType getType() const { return type; };

        std::regex getRegEx() const { return regex; };

        std::vector<XPLMDataRef> getDataRefs() const { return dataRefs; };

    private:
        int id;
        std::string name;
        CommandType type;
        std::regex regex;
        std::vector<XPLMDataRef> dataRefs;
    };
}

#endif //X_COPILOT_COMMANDMETADATA_H
