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
    class CommandRecognizer {
    public:
        explicit CommandRecognizer(const CommandMetadata metadata) : metadata{metadata} {}

        explicit CommandRecognizer() = default;

        virtual ~CommandRecognizer() = default;

        virtual int getId() const { return metadata.getId(); }

        virtual std::string getName() const { return metadata.getName(); }

        virtual bool commandRecognized(const std::string &) const;

        virtual CommandExecutor getExecutor(const std::string &);

    private:
        CommandMetadata metadata;
    };
}

#endif // COMMAND_H
