#ifndef X_COPILOT_UNIXRECOGNIZER_H
#define X_COPILOT_UNIXRECOGNIZER_H

#include <memory>
#include <boost/signals2.hpp>

#include "Microphone.h"
#include "MicrophoneHandler.h"
#include "PocketsphinxWrapper.h"
#include "Recognizer.h"

namespace xcopilot {
    class UnixRecognizer : public Recognizer, public MicrophoneHandler<short> {
    public:
        typedef boost::signals2::signal<void(const std::string &)> signal_t;

        explicit UnixRecognizer()
                : pocketsphinx{std::make_unique<Pocketsphinx>()}, microphone{std::make_unique<Microphone>()},
                    shouldDecode{false} {}
        explicit UnixRecognizer(std::unique_ptr<Pocketsphinx> p, std::unique_ptr<Microphone> m)
                : pocketsphinx{std::move(p)}, microphone{std::move(m)}, shouldDecode{false} {}

        void start();
        void stop();
        void handleAudio(const short *rawData, unsigned long frameCount);

        boost::signals2::connection connect(const signal_t::slot_type &subscriber) {
            return onRecognition.connect(subscriber);
        };
    private:
        std::unique_ptr<Pocketsphinx> pocketsphinx;
        std::unique_ptr<Microphone> microphone;
        bool shouldDecode;
        signal_t onRecognition;
    };
}

#endif //X_COPILOT_UNIXRECOGNIZER_H
