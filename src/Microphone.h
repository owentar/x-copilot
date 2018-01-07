#ifndef MICROPHONE_H
#define MICROPHONE_H

#include "portaudio.h"
#include "MicrophoneHandler.h"

namespace xcopilot {
    typedef short SAMPLE;

    class Microphone {
    public:
        Microphone() : stream{nullptr} {};

        virtual ~Microphone() = default;

        virtual void start(MicrophoneHandler<SAMPLE> *);

        virtual void stop();

        virtual bool isListening();

    private:
        void handlePaError(PaError error);

        PaStreamParameters getMicParams();

        PaStream *stream;
    };
}

#endif // MICROPHONE_H
