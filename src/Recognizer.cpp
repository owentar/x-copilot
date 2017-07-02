#include "Recognizer.h"

#include <iostream>

Recognizer::Recognizer(Pocketsphinx* p, Microphone* m) : pocketsphinx(p), microphone(m), shouldDecode(false)
{
    pocketsphinx->init();
    microphone->init();
}

Recognizer::~Recognizer()
{
    microphone->terminate();
}

void Recognizer::start()
{
    pocketsphinx->start();
    microphone->listen(this);
}

void Recognizer::handleAudio(const short* rawData, unsigned long frameCount)
{
    pocketsphinx->process(rawData, frameCount);

    if (pocketsphinx->isSpeaking())
    {
        shouldDecode = true;
    }
    else
    {
        if (shouldDecode)
        {
            shouldDecode = false;
            std::cout << "You just said: " << pocketsphinx->decode() << std::endl;
        }
    }
}
