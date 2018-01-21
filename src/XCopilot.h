#ifndef XCOPILOT_H
#define XCOPILOT_H

#include <memory>
#include <regex>
#include <utility>
#include <vector>

#include "Command.h"
#include "CommandExecutor.h"
#include "Microphone.h"
#include "PocketsphinxWrapper.h"
#include "Recognizer.h"

namespace xcopilot {
    class XCopilot {
    public:
        XCopilot(std::unique_ptr<xcopilot::Recognizer> recognizer) : recognizer{std::move(recognizer)}, pendingCommands{},
                                                                     commandProcessor{} {};

        virtual ~XCopilot() = default;

        void enable() { recognizer->start(); };

        void disable() { recognizer->stop(); };

        void configureForAircraft(const std::vector<std::shared_ptr<Command>>& commands);

        void addCommand(std::shared_ptr<Command> command) { commandProcessor.push_back(command); };

        bool hasPendingCommands() const { return !pendingCommands.empty(); };

        void recognizeCommand(const std::string &command);

        void executePendingCommands();

    private:
        XCopilot &operator=(XCopilot const &);

        std::unique_ptr<Recognizer> recognizer;
        std::vector<CommandExecutor> pendingCommands;
        std::vector<std::shared_ptr<Command>> commandProcessor;
    };
}

#endif // XCOPILOT_H
