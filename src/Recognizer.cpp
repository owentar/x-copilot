#include "Recognizer.h"

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
            onRecognition(pocketsphinx->decode());
        }
    }
}
