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

class XCopilot
{
    public:
        XCopilot(std::unique_ptr<xcopilot::Recognizer> recognizer) : recognizer{std::move(recognizer)}, commands{}, commandProcessor{} {};
        virtual ~XCopilot() = default;
        void enable() { recognizer->start(); };
        void disable() { recognizer->stop(); };
        void configureForAircraft(const char*, const char*, const char*);
        void addCommand(xcopilot::Command* command) { commandProcessor.push_back(command); };
        bool hasCommands() const { return !commands.empty(); };
        void recognizeCommand(const std::string& command);
        void executePendingCommands();

    private:
        XCopilot& operator=(XCopilot const&);

        std::unique_ptr<xcopilot::Recognizer> recognizer;
        std::vector<xcopilot::CommandExecutor> commands;
        std::vector<xcopilot::Command*> commandProcessor;
};

#endif // XCOPILOT_H
