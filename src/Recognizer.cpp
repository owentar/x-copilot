#include "Recognizer.h"

#include <iostream>

Recognizer::Recognizer(Pocketsphinx* p, Microphone* m) : pocketsphinx{p}, microphone{m}, shouldDecode{false}
{
    pocketsphinx->init();
    microphone->init();
}

Recognizer::~Recognizer()
{
    stop();
}

void Recognizer::start()
{
    pocketsphinx->start();
    microphone->listen(this);
}

void Recognizer::stop()
{
    microphone->terminate();
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
            onRecognition(pocketsphinx->decode());
        }
    }
}
