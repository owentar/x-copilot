#ifndef POCKETSPHINXWRAPPER_H
#define POCKETSPHINXWRAPPER_H

#include "pocketsphinx/pocketsphinx.h"
#include <string>

namespace xcopilot {
    class Pocketsphinx {
    public:
        explicit Pocketsphinx() {};

        virtual ~Pocketsphinx() = default;

        virtual void start();

        virtual void stop();

        virtual std::string decode();

        virtual void process(const short *rawData, unsigned long frameCount);

        virtual bool isSpeaking() const;

    private:
        ps_decoder_t *ps;
    };
}

#endif // POCKETSPHINXWRAPPER_H
