#include "PocketsphinxWrapper.h"
#include "Recognizer.h"
#include "Microphone.h"

#include <iostream>

int main(int argc, char *argv[]) {
    Microphone mic;
    Pocketsphinx pocketsphinx;
    Recognizer recognizer(&pocketsphinx, &mic);

    recognizer.connect([](const std::string phrase) { std::cout << phrase << std::endl; } );
    recognizer.start();

    while(true) { }

    return 0;
}
