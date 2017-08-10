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
    MOCK_METHOD0(init, void());
    MOCK_METHOD0(start, void());
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
    MOCK_METHOD1(listen, void(MicrophoneHandler<short>*));
};

class RecognizerTest : public Test
{
protected:
    short micData[10];
};

TEST_F(RecognizerTest, InConstructionIsNotListening)
{
    NiceMock<MicrophoneMock> microphone;
    EXPECT_CALL(microphone, listen(_)).Times(0);
    NiceMock<PocketsphinxMock> pocketsphinx;
    EXPECT_CALL(pocketsphinx, start()).Times(0);

    Recognizer recognizer(&pocketsphinx, &microphone);
}

TEST_F(RecognizerTest, WhenRecognizerIsStartedPocketsphinxIsInitialized)
{
    NiceMock<MicrophoneMock> microphone;
    NiceMock<PocketsphinxMock> pocketsphinx;
    Recognizer recognizer(&pocketsphinx, &microphone);
    EXPECT_CALL(pocketsphinx, start());

    recognizer.start();
}

TEST_F(RecognizerTest, WhenRecognizerIsStartedMicrophoneStartsListening)
{
    NiceMock<MicrophoneMock> microphone;
    NiceMock<PocketsphinxMock> pocketsphinx;
    Recognizer recognizer(&pocketsphinx, &microphone);
    EXPECT_CALL(microphone, listen(&recognizer));

    recognizer.start();
}

TEST_F(RecognizerTest, WhenSpeechIsNotRecognizedNoRecognitionIsNotified)
{
    NiceMock<MicrophoneMock> microphone;
    NiceMock<PocketsphinxMock> pocketsphinx;
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
