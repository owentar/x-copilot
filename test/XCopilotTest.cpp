#include "gmock/gmock.h"

#include <utility>
#include <memory>

#include "XCopilot.h"
#include "CommandRecognizer.h"
#include "Recognizer.h"
#include "util/XPlaneDataRefSDKMock.h"

#ifdef IBM
#include "WinRecognizer.h"
#else
#include "UnixRecognizer.h"
#endif

using namespace testing;
using namespace xcopilot;

#ifdef IBM
class RecognizerMock : public WinRecognizer
{
public:
    explicit RecognizerMock() : UnixRecognizer() {};
    MOCK_METHOD0(start, void());
    MOCK_METHOD0(stop, void());
};
#else
class RecognizerMock : public UnixRecognizer
{
public:
    explicit RecognizerMock() : UnixRecognizer() {};
    MOCK_METHOD0(start, void());
    MOCK_METHOD0(stop, void());
};
#endif

class CommandRecognizerMock : public CommandRecognizer
{
public:
    explicit CommandRecognizerMock(XPlaneDataRefSDK* xPLaneDatRefSDK) : CommandRecognizer(CommandMetadata("Test CommandRecognizer", CommandType::FLOAT, "test regex", {})) {};
    MOCK_CONST_METHOD1(commandRecognized, bool(const std::string&));
};

class XCopilotTest : public Test
{
public:
    XCopilotTest() : xPlaneDatRefSDK{}, xcopilot{std::move(std::make_unique<RecognizerMock>())} {};
protected:
    XPlaneDataRefSDKMock xPlaneDatRefSDK;
    XCopilot xcopilot;
};

TEST_F(XCopilotTest, ShouldQueueCommandWhenItIsRecognized)
{
    auto command = std::make_shared<NiceMock<CommandRecognizerMock>>(&xPlaneDatRefSDK);
    EXPECT_CALL(*command, commandRecognized(_))
        .Times(1)
        .WillOnce(Return(true));
    xcopilot.configureForAircraft({command});

    xcopilot.recognizeCommand("recognized command");

    ASSERT_TRUE(xcopilot.hasPendingCommands());
}

TEST_F(XCopilotTest, ShouldNotQueueCommandWhenItIsNotRecognized)
{
    auto command = std::make_shared<NiceMock<CommandRecognizerMock>>(&xPlaneDatRefSDK);
    EXPECT_CALL(*command, commandRecognized(_))
        .Times(1)
        .WillOnce(Return(false));
    xcopilot.configureForAircraft({command});

    xcopilot.recognizeCommand("unrecognized command");

    ASSERT_FALSE(xcopilot.hasPendingCommands());
}

// TODO: test execute pending commands
