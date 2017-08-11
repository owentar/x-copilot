#include "gmock/gmock.h"

#include "Command.h"

using namespace testing;

class CommandTest : public Test
{
protected:
    CommandTest() : command("Test", "^.*test$") {};

    Command command;
};

TEST_F(CommandTest, RecognizeCommandWhenPhraseDoesMatchRegEx)
{
    ASSERT_THAT(command.isRecognized("a test"), Eq(true));
}

TEST_F(CommandTest, DoesNotRecognizeCommandWhenPhraseDoesNotMatchRegEx)
{
    ASSERT_THAT(command.isRecognized("does not match"), Eq(false));
}

