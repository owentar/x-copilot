#ifndef POCKETSPHINXWRAPPER_H
#define POCKETSPHINXWRAPPER_H

#include "pocketsphinx/pocketsphinx.h"
#include <string>

class Pocketsphinx
{
    public:
        explicit Pocketsphinx() {};
        virtual ~Pocketsphinx() = default;
        virtual void init();
        virtual void start();
        virtual void end();
        virtual std::string decode();
        virtual void process(const short* rawData, unsigned long frameCount);
        virtual bool isSpeaking() const;

    private:
        ps_decoder_t* ps;
};

#endif // POCKETSPHINXWRAPPER_H
