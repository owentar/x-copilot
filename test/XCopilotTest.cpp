#include <gmock.h>

#include "XCopilot.h"
#include "Command.h"

using namespace testing;

class CommandMock : public Command
{
public:
    CommandMock() : Command("Test Command", "test regex") {};
    MOCK_CONST_METHOD1(isRecognized, bool(const std::string&));
};

class XCopilotTest : public Test
{
protected:
    XCopilot* xcopilot;
    void SetUp()
    {
        xcopilot = XCopilot::getInstance();
    }
    void TearDown()
    {
        XCopilot::releaseInstance();
    }
};

TEST_F(XCopilotTest, ShouldQueueCommandWhenItIsRecognized)
{
    NiceMock<CommandMock> command;
    EXPECT_CALL(command, isRecognized(_))
        .Times(1)
        .WillOnce(Return(true));
    xcopilot->addCommand(&command);

    xcopilot->recognizeCommand("recognized command");

    ASSERT_TRUE(xcopilot->hasCommands());
}

TEST_F(XCopilotTest, ShouldNotQueueCommandWhenItIsNotRecognized)
{
    NiceMock<CommandMock> command;
    EXPECT_CALL(command, isRecognized(_))
        .Times(1)
        .WillOnce(Return(false));
    xcopilot->addCommand(&command);

    xcopilot->recognizeCommand("unrecognized command");

    ASSERT_FALSE(xcopilot->hasCommands());
}
