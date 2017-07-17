#ifndef XCOPILOT_H
#define XCOPILOT_H

#include "Recognizer.h"
#include "PocketsphinxWrapper.h"
#include "Microphone.h"

class XCopilot
{
    public:
        static XCopilot* getInstance();
        void enable();
        void disable();
        void configureForAircraft(const char*, const char*, const char*);

    private:
        XCopilot();
        XCopilot& operator=(XCopilot const&) { return *instance; };
        virtual ~XCopilot() {};

        static XCopilot* instance;
        Microphone microphone;
        Pocketsphinx pocketsphinx;
        Recognizer recognizer;
};

#endif // XCOPILOT_H
