#include "PocketsphinxWrapper.h"
#include "Recognizer.h"
#include "Microphone.h"

int main3(int argc, char *argv[]) {
    Microphone mic;
    Pocketsphinx pocketsphinx;
    Recognizer recognizer(&pocketsphinx, &mic);

    recognizer.start();

    while(true) { }

    return 0;
}