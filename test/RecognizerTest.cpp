#include "gmock/gmock.h"

#include "PocketsphinxWrapper.h"
#include "Recognizer.h"
#include "Microphone.h"
#include "MicrophoneHandler.h"

using namespace testing;

class PocketsphinxMock : public Pocketsphinx
{
public:
    virtual ~PocketsphinxMock() {};
    MOCK_METHOD0(start, void());
    MOCK_METHOD0(stop, void());
    MOCK_METHOD2(process, void(const short*, unsigned long));
    MOCK_METHOD0(decode, std::string());
    MOCK_CONST_METHOD0(isSpeaking, bool());
};

class MicrophoneMock : public Microphone
{
public:
    virtual ~MicrophoneMock() {};
    MOCK_METHOD0(init, void());
    MOCK_METHOD0(terminate, void());
    MOCK_METHOD0(isListening, bool());
    MOCK_METHOD1(listen, void(MicrophoneHandler<short>*));
};

class RecognizerTest : public Test
{
protected:
    short micData[10];
    NiceMock<MicrophoneMock> microphone;
    NiceMock<PocketsphinxMock> pocketsphinx;

};

TEST_F(RecognizerTest, InConstructionIsNotListening)
{
    EXPECT_CALL(microphone, listen(_)).Times(0);
    EXPECT_CALL(pocketsphinx, start()).Times(0);

    Recognizer recognizer(&pocketsphinx, &microphone);
}

TEST_F(RecognizerTest, WhenRecognizerIsStartedPocketsphinxIsInitialized)
{
    EXPECT_CALL(pocketsphinx, start());
    Recognizer recognizer(&pocketsphinx, &microphone);

    recognizer.start();
}

TEST_F(RecognizerTest, WhenRecognizerIsStartedMicrophoneStartsListening)
{
    Recognizer recognizer(&pocketsphinx, &microphone);
    EXPECT_CALL(microphone, init());
    EXPECT_CALL(microphone, listen(&recognizer));

    recognizer.start();
}

TEST_F(RecognizerTest, WhenSpeechIsNotRecognizedNoRecognitionIsNotified)
{
    EXPECT_CALL(pocketsphinx, isSpeaking())
        .WillOnce(Return(true))
        .WillOnce(Return(false));
    EXPECT_CALL(pocketsphinx, decode())
        .WillOnce(Return("test"));
    Recognizer recognizer(&pocketsphinx, &microphone);
    recognizer.connect([] (const std::string& msg) { ASSERT_THAT(msg, Eq("test")); });
    recognizer.start();

    recognizer.handleAudio(micData, 10);
    recognizer.handleAudio(micData, 10);
}

TEST_F(RecognizerTest, WhenRecognizerIsStoppedTerminatesMicrophone)
{
    EXPECT_CALL(microphone, terminate());

    Recognizer recognizer(&pocketsphinx, &microphone);
    recognizer.start();
    recognizer.stop();
}

TEST_F(RecognizerTest, WhenRecognizerIsStoppedTerminatesPocketsphinx)
{
    EXPECT_CALL(pocketsphinx, stop());

    Recognizer recognizer(&pocketsphinx, &microphone);
    recognizer.start();
    recognizer.stop();
}
