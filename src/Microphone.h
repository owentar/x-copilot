#ifndef MICROPHONE_H
#define MICROPHONE_H

#include "portaudio.h"
#include "MicrophoneHandler.h"

typedef short SAMPLE;

class Microphone
{
    public:
        Microphone();
        virtual ~Microphone();
        virtual void listen(MicrophoneHandler<SAMPLE>*);
        bool isListening();

    private:
        void handlePaError(PaError error);
        PaStreamParameters getMicParams();

        PaStream* stream;
};

#endif // MICROPHONE_H
