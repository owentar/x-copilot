#ifndef COMMAND_H
#define COMMAND_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <vector>

#include "CommandExecutor.h"
#include "CommandMetadata.h"

namespace xcopilot {
    class Command {
    public:
        explicit Command(const CommandMetadata metadata) : metadata{metadata} {}

        explicit Command() = default;

        virtual ~Command() = default;

        virtual std::string getName() const { return metadata.getName(); }

        virtual bool isRecognized(const std::string &) const;

        virtual CommandExecutor getExecutor(const std::string &);

    private:
        CommandMetadata metadata;
    };
}

#endif // COMMAND_H
