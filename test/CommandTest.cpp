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

TEST_F(CommandTest, GetAltitudeValueFromCommand)
{
    Command c("Altimeter", "^set altitude ((?:(?:\\d|zero|one|two|three|four|five|six|seven|eight|nine)\\s?){3,5})$");
    ASSERT_THAT(c.getValue("set altitude three five zero zero"), Eq(3500));
}
