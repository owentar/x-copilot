#include "gmock/gmock.h"

#include <memory>
#include <utility>

#include "PocketsphinxWrapper.h"
#include "UnixRecognizer.h"
#include "Microphone.h"
#include "MicrophoneHandler.h"

using namespace testing;
using namespace xcopilot;

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

class UnixRecognizerTest : public Test
{
protected:
    short micData[10]{};
    std::unique_ptr<NiceMock<MicrophoneMock>> microphone;
    std::unique_ptr<NiceMock<PocketsphinxMock>> pocketsphinx;

    UnixRecognizerTest() : pocketsphinx{std::make_unique<NiceMock<PocketsphinxMock>>()}, microphone{std::make_unique<NiceMock<MicrophoneMock>>()} {};
};

TEST_F(UnixRecognizerTest, InConstructionIsNotListening)
{
    EXPECT_CALL(*microphone, start(_)).Times(0);
    EXPECT_CALL(*pocketsphinx, start()).Times(0);

    UnixRecognizer recognizer(std::move(pocketsphinx), std::move(microphone));
}

TEST_F(UnixRecognizerTest, WhenRecognizerIsStartedPocketsphinxIsInitialized)
{
    EXPECT_CALL(*pocketsphinx, start());
    UnixRecognizer recognizer(std::move(pocketsphinx), std::move(microphone));

    recognizer.start();
}

TEST_F(UnixRecognizerTest, WhenRecognizerIsStartedMicrophoneStartsListening)
{
    EXPECT_CALL(*microphone, start(testing::_));
    UnixRecognizer recognizer(std::move(pocketsphinx), std::move(microphone));

    recognizer.start();
}

TEST_F(UnixRecognizerTest, WhenSpeechIsNotRecognizedNoRecognitionIsNotified)
{
    EXPECT_CALL(*pocketsphinx, isSpeaking())
        .WillOnce(Return(true))
        .WillOnce(Return(false));
    EXPECT_CALL(*pocketsphinx, decode())
        .WillOnce(Return("test"));
    UnixRecognizer recognizer(std::move(pocketsphinx), std::move(microphone));
    recognizer.connect([] (const std::string& msg) { ASSERT_THAT(msg, Eq("test")); });
    recognizer.start();

    recognizer.handleAudio(micData, 10);
    recognizer.handleAudio(micData, 10);
}

TEST_F(UnixRecognizerTest, WhenRecognizerIsStoppedTerminatesMicrophone)
{
    EXPECT_CALL(*microphone, stop());

    UnixRecognizer recognizer(std::move(pocketsphinx), std::move(microphone));
    recognizer.start();
    recognizer.stop();
}

TEST_F(UnixRecognizerTest, WhenRecognizerIsStoppedTerminatesPocketsphinx)
{
    EXPECT_CALL(*pocketsphinx, stop());

    UnixRecognizer recognizer(std::move(pocketsphinx), std::move(microphone));
    recognizer.start();
    recognizer.stop();
}
