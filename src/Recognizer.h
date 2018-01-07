#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include <memory>
#include <utility>

#include <boost/signals2.hpp>

#include "Microphone.h"
#include "MicrophoneHandler.h"
#include "PocketsphinxWrapper.h"

class Recognizer : public MicrophoneHandler<short>
{
public:
    typedef boost::signals2::signal<void (const std::string&)> signal_t;

    explicit Recognizer(std::unique_ptr<xcopilot::Pocketsphinx> p, std::unique_ptr<xcopilot::Microphone> m)
            : pocketsphinx{std::move(p)}, microphone{std::move(m)}, shouldDecode{false} {};
    virtual ~Recognizer() = default;
    virtual void start();
    virtual void stop();
    void handleAudio(const short* rawData, unsigned long frameCount);
    boost::signals2::connection connect(const signal_t::slot_type &subscriber)
    {
        return onRecognition.connect(subscriber);
    };

protected:
    explicit Recognizer() : pocketsphinx{nullptr}, microphone{nullptr}, shouldDecode{false} {};

private:
    std::unique_ptr<xcopilot::Pocketsphinx> pocketsphinx;
    std::unique_ptr<xcopilot::Microphone> microphone;
    bool shouldDecode;
    signal_t onRecognition;
};

#endif // RECOGNIZER_H
