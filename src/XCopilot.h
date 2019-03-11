#ifndef XCOPILOT_H
#define XCOPILOT_H

#include <memory>
#include <regex>
#include <utility>
#include <vector>

#include "Command.h"
#include "CommandExecutor.h"
#include "Recognizer.h"

namespace xcopilot {
    class XCopilot {
    public:
        XCopilot(std::unique_ptr<xcopilot::Recognizer> recognizer) : recognizer{std::move(recognizer)} {};

        virtual ~XCopilot() = default;

        void enable() { recognizer->start(); };

        void disable() { recognizer->stop(); };

        void configureForAircraft(const std::vector<std::shared_ptr<Command>>& commands);

		std::vector<CommandExecutor> getPendingCommands();

    private:
        XCopilot &operator=(XCopilot const &);

        std::unique_ptr<Recognizer> recognizer;
    };
}

#endif // XCOPILOT_H
