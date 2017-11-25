#ifndef XCOPILOT_H
#define XCOPILOT_H

#include <memory>
#include <regex>
#include <utility>
#include <vector>

#include "Recognizer.h"
#include "PocketsphinxWrapper.h"
#include "Microphone.h"
#include "Command.h"

class XCopilot
{
    public:
        XCopilot(std::unique_ptr<Recognizer> recognizer) : recognizer{std::move(recognizer)}, commands{}, commandProcessor{} {};
        virtual ~XCopilot() {};
        void enable() { recognizer->start(); };
        void disable() { recognizer->stop(); };
        void configureForAircraft(const char*, const char*, const char*);
        void addCommand(Command* command) { commandProcessor.push_back(command); };
        bool hasCommands() const { return !commands.empty(); };
        void recognizeCommand(const std::string& command);
        void executePendingCommands();

    private:
        XCopilot& operator=(XCopilot const&);

        std::unique_ptr<Recognizer> recognizer;
        std::vector<CommandExecutorPtr> commands;
        std::vector<Command*> commandProcessor;
};

#endif // XCOPILOT_H
