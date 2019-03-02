#include "gmock/gmock.h"

#include "CommandRecognizer.h"
#include "CommandMetadata.h"

using namespace testing;
using namespace xcopilot;

class CommandRecognizerTest : public Test
{
public:
    CommandRecognizerTest() : commandRecognizer(CommandMetadata("Test", CommandType::FLOAT, "^.*test$", {})) {};
protected:
    CommandRecognizer commandRecognizer;
};

TEST_F(CommandRecognizerTest, RecognizeCommandWhenPhraseDoesMatchRegEx)
{
    ASSERT_THAT(commandRecognizer.commandRecognized("a test"), Eq(true));
}

TEST_F(CommandRecognizerTest, DoesNotRecognizeCommandWhenPhraseDoesNotMatchRegEx)
{
    ASSERT_THAT(commandRecognizer.commandRecognized("does not match"), Eq(false));
}
