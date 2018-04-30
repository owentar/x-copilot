#include "gmock/gmock.h"

#include <utility>
#include <memory>

#include "XCopilot.h"
#include "CommandRecognizer.h"
#include "Recognizer.h"
#include "util/XPlaneDataRefSDKMock.h"

using namespace testing;
using namespace xcopilot;

class RecognizerMock : public Recognizer
{
public:
    explicit RecognizerMock() : Recognizer() {};
};

class CommandMock : public CommandRecognizer
{
public:
    explicit CommandMock(XPlaneDataRefSDK* xPLaneDatRefSDK) : CommandRecognizer(CommandMetadata("Test CommandRecognizer", CommandType::FLOAT, "test regex", {})) {};
    MOCK_CONST_METHOD1(isRecognized, bool(const std::string&));
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
    auto command = std::make_shared<NiceMock<CommandMock>>(&xPlaneDatRefSDK);
    EXPECT_CALL(*command, isRecognized(_))
        .Times(1)
        .WillOnce(Return(true));
    xcopilot.configureForAircraft({command});

    xcopilot.recognizeCommand("recognized command");

    ASSERT_TRUE(xcopilot.hasPendingCommands());
}

TEST_F(XCopilotTest, ShouldNotQueueCommandWhenItIsNotRecognized)
{
    auto command = std::make_shared<NiceMock<CommandMock>>(&xPlaneDatRefSDK);
    EXPECT_CALL(*command, isRecognized(_))
        .Times(1)
        .WillOnce(Return(false));
    xcopilot.configureForAircraft({command});

    xcopilot.recognizeCommand("unrecognized command");

    ASSERT_FALSE(xcopilot.hasPendingCommands());
}

// TODO: test execute pending commands
