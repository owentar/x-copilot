#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include "Microphone.h"
#include "MicrophoneHandler.h"
#include "PocketsphinxWrapper.h"

#include <boost/signals2.hpp>


class Recognizer : public MicrophoneHandler<short>
{
public:
    typedef boost::signals2::signal<void (const std::string&)> signal_t;

    explicit Recognizer(Pocketsphinx* p, Microphone* m);
    virtual ~Recognizer();
    void start();
    void stop();
    void handleAudio(const short* rawData, unsigned long frameCount);
    boost::signals2::connection connect(const signal_t::slot_type &subscriber)
    {
        return onRecognition.connect(subscriber);
    };

private:
    Pocketsphinx* pocketsphinx;
    Microphone* microphone;
    bool shouldDecode;
    signal_t onRecognition;
};

#endif // RECOGNIZER_H
