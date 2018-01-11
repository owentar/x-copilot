#include "Microphone.h"

#include <iostream>

#include <boost/format.hpp>
#include <portaudio.h>

#include "Logger.h"
#include "MicrophoneHandler.h"

#define SAMPLE_RATE         (16000)
#define NUM_CHANNELS        (1)

#define PA_SAMPLE_TYPE      paInt16

using namespace xcopilot;
using boost::format;

static int micCallback(const void* input,
                        void* output,
                        unsigned long frameCount,
                        const PaStreamCallbackTimeInfo* timeInfo,
                        PaStreamCallbackFlags statusFlags,
                        void* userData);

void Microphone::start(MicrophoneHandler<SAMPLE>* handler)
{
    PaError error = Pa_Initialize();
    handlePaError(error);

    PaStreamParameters inputParameters = getMicParams();
    error = Pa_OpenStream(&stream, &inputParameters, NULL, SAMPLE_RATE, 256, paClipOff, micCallback, handler);
    handlePaError(error);

    error = Pa_StartStream(stream);
    handlePaError(error);
}

void Microphone::stop()
{
    if (isListening())
    {
        PaError error = Pa_StopStream(stream);
        handlePaError(error);
    }

    PaError error = Pa_Terminate();
    handlePaError(error);
}

bool Microphone::isListening()
{
    return Pa_IsStreamActive(stream) == 1;
}

void Microphone::handlePaError(PaError error)
{
    if (error != paNoError) Logger::getInstance()->error(format("Microphone error: %1%") % Pa_GetErrorText(error));
}

PaStreamParameters Microphone::getMicParams()
{
    PaStreamParameters inputParameters;
    inputParameters.device = Pa_GetDefaultInputDevice();
    if (inputParameters.device == paNoDevice) {
        Logger::getInstance()->error("Microphone error: No default input device");
    }
    inputParameters.channelCount = NUM_CHANNELS;
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;
    return inputParameters;
}

static int micCallback(const void* input,
                        void* output,
                        unsigned long frameCount,
                        const PaStreamCallbackTimeInfo* timeInfo,
                        PaStreamCallbackFlags statusFlags,
                        void* userData)
{
    MicrophoneHandler<SAMPLE>* handler = (MicrophoneHandler<SAMPLE>*) userData;
    const SAMPLE* rawData = (const SAMPLE*) input;

    handler->handleAudio(rawData, frameCount);

    return paContinue;
}
