#ifndef X_COPILOT_UNIXRECOGNIZER_H
#define X_COPILOT_UNIXRECOGNIZER_H

#include <memory>

#include "Microphone.h"
#include "MicrophoneHandler.h"
#include "PocketsphinxWrapper.h"
#include "Recognizer.h"

namespace xcopilot {
    class UnixRecognizer : public Recognizer, public MicrophoneHandler<short> {
    public:
        explicit UnixRecognizer()
                : pocketsphinx{std::make_unique<Pocketsphinx>()}, microphone{std::make_unique<Microphone>()},
                    shouldDecode{false}, commandsRecognized{} {}
        explicit UnixRecognizer(std::unique_ptr<Pocketsphinx> p, std::unique_ptr<Microphone> m)
                : pocketsphinx{std::move(p)}, microphone{std::move(m)}, shouldDecode{false}, commandsRecognized{} {}

        virtual std::vector<CommandExecutor> getRecognizedCommands() { return commandsRecognized; }

        virtual void start();
        virtual void stop();
        virtual void handleAudio(const short *rawData, unsigned long frameCount);
    private:
        std::unique_ptr<Pocketsphinx> pocketsphinx;
        std::unique_ptr<Microphone> microphone;
        bool shouldDecode;
        std::vector<CommandExecutor> commandsRecognized;

        void recognizeCommand(const std::string& phrase);
    };
}

#endif //X_COPILOT_UNIXRECOGNIZER_H
