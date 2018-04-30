#include "gmock/gmock.h"

#include "Command.h"
#include "CommandMetadata.h"
#include "XPlaneDataRefSDK.h"
#include "util/XPlaneDataRefSDKMock.h"

using namespace testing;
using namespace xcopilot;

class CommandTest : public Test
{
protected:
    NiceMock<XPlaneDataRefSDKMock> xPlaneDataRefSDKMock;
    Command command;

    CommandTest() : xPlaneDataRefSDKMock{}, command(CommandMetadata("Test", CommandType::FLOAT, "^.*test$", {})) {};
};

TEST_F(CommandTest, RecognizeCommandWhenPhraseDoesMatchRegEx)
{
    ASSERT_THAT(command.isRecognized("a test"), Eq(true));
}

TEST_F(CommandTest, DoesNotRecognizeCommandWhenPhraseDoesNotMatchRegEx)
{
    ASSERT_THAT(command.isRecognized("does not match"), Eq(false));
}
