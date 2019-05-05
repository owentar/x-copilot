#include "gmock/gmock.h"

#include <memory>
#include <utility>

#include "PocketsphinxWrapper.h"
#include "UnixRecognizer.h"
#include "Microphone.h"
#include "MicrophoneHandler.h"
#include "util/XPlaneDataRefSDKMock.h"

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

class CommandRecognizerMock : public CommandRecognizer
{
public:
    explicit CommandRecognizerMock(XPlaneDataRefSDK* xPLaneDatRefSDK) : CommandRecognizer(CommandMetadata("Test CommandRecognizer", CommandType::FLOAT, "test regex", {})) {};
    MOCK_CONST_METHOD1(commandRecognized, bool(const std::string&));
};

class UnixRecognizerTest : public Test
{
protected:
    short micData[10]{};
    XPlaneDataRefSDKMock xPlaneDatRefSDK;
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

TEST_F(UnixRecognizerTest, ShouldNotQueueCommandWhenItIsNotRecognized)
{
    auto command = std::make_shared<NiceMock<CommandRecognizerMock>>(&xPlaneDatRefSDK);
    EXPECT_CALL(*pocketsphinx, isSpeaking())
            .WillOnce(Return(true))
            .WillOnce(Return(false));
    EXPECT_CALL(*pocketsphinx, decode())
            .WillOnce(Return("test"));
    EXPECT_CALL(*command, commandRecognized("test"))
            .Times(1)
            .WillOnce(Return(false));
    UnixRecognizer recognizer(std::move(pocketsphinx), std::move(microphone));
    recognizer.configure({command});
    recognizer.handleAudio(micData, 10);
    recognizer.handleAudio(micData, 10);

    ASSERT_TRUE(recognizer.getRecognizedCommands().empty());
}

TEST_F(UnixRecognizerTest, ShouldQueueRecognizedCommands)
{
    auto command = std::make_shared<NiceMock<CommandRecognizerMock>>(&xPlaneDatRefSDK);
    EXPECT_CALL(*pocketsphinx, isSpeaking())
            .WillOnce(Return(true))
            .WillOnce(Return(false));
    EXPECT_CALL(*pocketsphinx, decode())
            .WillOnce(Return("test"));
    EXPECT_CALL(*command, commandRecognized("test"))
            .Times(1)
            .WillOnce(Return(true));
    UnixRecognizer recognizer(std::move(pocketsphinx), std::move(microphone));
    recognizer.configure({command});
    recognizer.handleAudio(micData, 10);
    recognizer.handleAudio(micData, 10);

    ASSERT_FALSE(recognizer.getRecognizedCommands().empty());
}
