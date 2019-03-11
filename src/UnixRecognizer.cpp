#include "Recognizer.h"

using namespace xcopilot;

void Recognizer::start()
{
    pocketsphinx->start();
    microphone->start(this);
}

void Recognizer::stop()
{
    pocketsphinx->stop();
    microphone->stop();
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
