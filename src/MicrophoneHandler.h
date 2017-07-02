#ifndef MICROPHONEHANDLER_H_INCLUDED
#define MICROPHONEHANDLER_H_INCLUDED

template<class T>
class MicrophoneHandler
{
public:
    virtual void handleAudio(const T* rawData, unsigned long frameCount) = 0;
};

#endif // MICROPHONEHANDLER_H_INCLUDED
