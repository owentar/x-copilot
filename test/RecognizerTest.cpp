#include "gmock/gmock.h"

#include <memory>
#include <utility>

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
    MOCK_METHOD1(start, void(MicrophoneHandler<short>*));
    MOCK_METHOD0(stop, void());
    MOCK_METHOD0(isListening, bool());
};

class RecognizerTest : public Test
{
protected:
    short micData[10]{};
    std::unique_ptr<NiceMock<MicrophoneMock>> microphone;
    std::unique_ptr<NiceMock<PocketsphinxMock>> pocketsphinx;

    RecognizerTest() : pocketsphinx{std::make_unique<NiceMock<PocketsphinxMock>>()}, microphone{std::make_unique<NiceMock<MicrophoneMock>>()} {};
};

TEST_F(RecognizerTest, InConstructionIsNotListening)
{
    EXPECT_CALL(*microphone, start(_)).Times(0);
    EXPECT_CALL(*pocketsphinx, start()).Times(0);

    Recognizer recognizer(std::move(pocketsphinx), std::move(microphone));
}

TEST_F(RecognizerTest, WhenRecognizerIsStartedPocketsphinxIsInitialized)
{
    EXPECT_CALL(*pocketsphinx, start());
    Recognizer recognizer(std::move(pocketsphinx), std::move(microphone));

    recognizer.start();
}

TEST_F(RecognizerTest, WhenRecognizerIsStartedMicrophoneStartsListening)
{
    EXPECT_CALL(*microphone, start(testing::_));
    Recognizer recognizer(std::move(pocketsphinx), std::move(microphone));

    recognizer.start();
}

TEST_F(RecognizerTest, WhenSpeechIsNotRecognizedNoRecognitionIsNotified)
{
    EXPECT_CALL(*pocketsphinx, isSpeaking())
        .WillOnce(Return(true))
        .WillOnce(Return(false));
    EXPECT_CALL(*pocketsphinx, decode())
        .WillOnce(Return("test"));
    Recognizer recognizer(std::move(pocketsphinx), std::move(microphone));
    recognizer.connect([] (const std::string& msg) { ASSERT_THAT(msg, Eq("test")); });
    recognizer.start();

    recognizer.handleAudio(micData, 10);
    recognizer.handleAudio(micData, 10);
}

TEST_F(RecognizerTest, WhenRecognizerIsStoppedTerminatesMicrophone)
{
    EXPECT_CALL(*microphone, stop());

    Recognizer recognizer(std::move(pocketsphinx), std::move(microphone));
    recognizer.start();
    recognizer.stop();
}

TEST_F(RecognizerTest, WhenRecognizerIsStoppedTerminatesPocketsphinx)
{
    EXPECT_CALL(*pocketsphinx, stop());

    Recognizer recognizer(std::move(pocketsphinx), std::move(microphone));
    recognizer.start();
    recognizer.stop();
}
