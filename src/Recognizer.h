#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include <memory>
#include <utility>

namespace xcopilot {
    class Recognizer {
    public:
        virtual ~Recognizer() = default;
        virtual void start() = 0;
        virtual void stop() = 0;
    };
}

#endif // RECOGNIZER_H
