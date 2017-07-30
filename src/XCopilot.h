#ifndef XCOPILOT_H
#define XCOPILOT_H

#include <queue>
#include <vector>
#include <regex>

#include "Recognizer.h"
#include "PocketsphinxWrapper.h"
#include "Microphone.h"
#include "Command.h"

class XCopilot
{
    public:
        static XCopilot* getInstance();
        static void releaseInstance();
        void enable();
        void disable();
        void configureForAircraft(const char*, const char*, const char*);
        void addCommand(Command* command) { commandProcessor.push_back(command); };
        bool hasCommands() const { return !commands.empty(); };
        void recognizeCommand(const std::string& command);

    private:
        XCopilot();
        XCopilot& operator=(XCopilot const&) { return *instance; };
        virtual ~XCopilot() {};

        static XCopilot* instance;
        Microphone microphone;
        Pocketsphinx pocketsphinx;
        Recognizer recognizer;
        std::queue<int> commands;
        std::vector<Command*> commandProcessor;
};

#endif // XCOPILOT_H
