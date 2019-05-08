#ifndef XCOPILOT_H
#define XCOPILOT_H

#include <memory>
#include <regex>
#include <utility>
#include <vector>

#include "defs.h"
#include "CommandRecognizer.h"
#include "CommandExecutor.h"
#include "Recognizer.h"

namespace xcopilot {
    class EXPORT XCopilot {
    public:
        XCopilot(std::unique_ptr<xcopilot::Recognizer> recognizer)
            : recognizer{std::move(recognizer)} {};

        virtual ~XCopilot() = default;

        void enable() { recognizer->start(); };

        void disable() { recognizer->stop(); };

        void configureForAircraft(const std::vector<std::shared_ptr<CommandRecognizer>>& commands);

        std::vector<CommandExecutor> getPendingCommands() { return recognizer->getRecognizedCommands(); }

    private:
        XCopilot &operator=(XCopilot const &);

        std::unique_ptr<Recognizer> recognizer;
    };
}

#endif // XCOPILOT_H
