#ifndef WINRECOGNIZER_H
#define WINRECOGNIZER_H

#include <sapi.h>

#define _ATL_APARTMENT_THREADED

#include <atlbase.h>

#include "CommandExecutor.h"
#include "Recognizer.h"

namespace xcopilot {
    class __declspec(dllexport) WinRecognizer : public Recognizer {
    public:
        virtual void start();
        virtual void stop();
        virtual std::vector<CommandExecutor> getRecognizedCommands();
    private:
        CComPtr<ISpObjectToken> recognizerToken;
        CComPtr<ISpObjectToken>	audioToken;
        CComPtr<ISpAudio> audio;
        CComPtr<ISpRecognizer> recognizer;
        CComPtr<ISpRecoContext> context;
        CComPtr<ISpRecoGrammar> grammar;
    };
}

#endif // WINRECOGNIZER_H
