#include "UnixRecognizer.h"

using namespace xcopilot;

void UnixRecognizer::start()
{
    pocketsphinx->start();
    microphone->start(this);
}

void UnixRecognizer::stop()
{
    pocketsphinx->stop();
    microphone->stop();
}

void UnixRecognizer::handleAudio(const short* rawData, unsigned long frameCount)
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
