#include "gmock/gmock.h"

#include "CommandRecognizer.h"
#include "CommandMetadata.h"
#include "util/XPlaneDataRefSDKMock.h"

using namespace testing;
using namespace xcopilot;

class CommandRecognizerTest : public Test
{
protected:
    NiceMock<XPlaneDataRefSDKMock> xPlaneDataRefSDKMock;
    CommandRecognizer commandRecognizer;

    CommandRecognizerTest() : xPlaneDataRefSDKMock{}, commandRecognizer(CommandMetadata("Test", CommandType::FLOAT, "^.*test$", {})) {};
};

TEST_F(CommandRecognizerTest, RecognizeCommandWhenPhraseDoesMatchRegEx)
{
    ASSERT_THAT(commandRecognizer.isRecognized("a test"), Eq(true));
}

TEST_F(CommandRecognizerTest, DoesNotRecognizeCommandWhenPhraseDoesNotMatchRegEx)
{
    ASSERT_THAT(commandRecognizer.isRecognized("does not match"), Eq(false));
}
