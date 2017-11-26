#include "Recognizer.h"

void Recognizer::start()
{
    microphone->init();
    pocketsphinx->start();
    microphone->listen(this);
}

void Recognizer::stop()
{
    pocketsphinx->stop();
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
