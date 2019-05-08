#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include <memory>
#include <utility>
#include <vector>

#include "defs.h"
#include "CommandExecutor.h"
#include "CommandRecognizer.h"

namespace xcopilot {
    class EXPORT Recognizer {
    public:
        virtual ~Recognizer() = default;

        virtual void configure(const std::vector<std::shared_ptr<CommandRecognizer>>& commands) { this->commands = commands; }
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual std::vector<CommandExecutor> getRecognizedCommands() = 0;

    protected:
        std::vector<std::shared_ptr<CommandRecognizer>> commands;
    };
}

#endif // RECOGNIZER_H
