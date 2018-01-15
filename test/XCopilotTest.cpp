#include "gmock/gmock.h"

#include <utility>
#include <memory>

#include "XCopilot.h"
#include "Command.h"
#include "Recognizer.h"
#include "XPlaneDataRefSDK.h"

using namespace testing;
using namespace xcopilot;

class RecognizerMock : public Recognizer
{
public:
    explicit RecognizerMock() : Recognizer() {};
};

class XPlaneDataRefSDKMock : public XPlaneDataRefSDK
{
public:
//    MOCK_METHOD1(findDataRef, XPLMDataRef(const std::string&));
};

class CommandMock : public Command
{
public:
    explicit CommandMock(XPlaneDataRefSDK* xPLaneDatRefSDK) : Command("Test Command", CommandType::FLOAT, "test regex", {"dataRefId"}, xPLaneDatRefSDK) {};
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
    NiceMock<CommandMock> command(&xPlaneDatRefSDK);
    EXPECT_CALL(command, isRecognized(_))
        .Times(1)
        .WillOnce(Return(true));
    xcopilot.addCommand(&command);

    xcopilot.recognizeCommand("recognized command");

    ASSERT_TRUE(xcopilot.hasCommands());
}

TEST_F(XCopilotTest, ShouldNotQueueCommandWhenItIsNotRecognized)
{
    NiceMock<CommandMock> command(&xPlaneDatRefSDK);
    EXPECT_CALL(command, isRecognized(_))
        .Times(1)
        .WillOnce(Return(false));
    xcopilot.addCommand(&command);

    xcopilot.recognizeCommand("unrecognized command");

    ASSERT_FALSE(xcopilot.hasCommands());
}

// TODO: test execute pending commands
