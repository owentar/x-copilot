#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include "Microphone.h"
#include "MicrophoneHandler.h"
#include "PocketsphinxWrapper.h"


class Recognizer : public MicrophoneHandler<short>
{
public:
    explicit Recognizer(Pocketsphinx* p, Microphone* m);
    virtual ~Recognizer();
    void start();
    void stop();
    void handleAudio(const short* rawData, unsigned long frameCount);

protected:

private:
    Pocketsphinx* pocketsphinx;
    Microphone* microphone;
    bool shouldDecode;
};

#endif // RECOGNIZER_H
