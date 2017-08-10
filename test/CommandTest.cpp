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
    ASSERT_TRUE(command.isRecognized("a test"));
}

TEST_F(CommandTest, DoesNotRecognizeCommandWhenPhraseDoesNotMatchRegEx)
{
    ASSERT_FALSE(command.isRecognized("does not match"));
}

