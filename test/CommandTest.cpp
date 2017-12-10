#include "gmock/gmock.h"

#include "Command.h"
#include "XPlaneDataRefSDK.h"

using namespace testing;

class XPlaneDataRefSDKMock : public XPlaneDataRefSDK
{
public:
    MOCK_METHOD1(findDataRef, XPLMDataRef(const std::string&));
    MOCK_CONST_METHOD1(getValue, int(XPLMDataRef));
    MOCK_CONST_METHOD2(setValue, void(XPLMDataRef, int));
};

class CommandTest : public Test
{
protected:
    NiceMock<XPlaneDataRefSDKMock> xPlaneDataRefSDKMock;
    Command command;

    CommandTest() : xPlaneDataRefSDKMock{}, command("Test", "^.*test$", {"dataRefId"}, &xPlaneDataRefSDKMock) {};
};

TEST_F(CommandTest, RecognizeCommandWhenPhraseDoesMatchRegEx)
{
    ASSERT_THAT(command.isRecognized("a test"), Eq(true));
}

TEST_F(CommandTest, DoesNotRecognizeCommandWhenPhraseDoesNotMatchRegEx)
{
    ASSERT_THAT(command.isRecognized("does not match"), Eq(false));
}

TEST_F(CommandTest, GetDataRefsIdsWhenCommandIsConstructed)
{
    EXPECT_CALL(xPlaneDataRefSDKMock, findDataRef("dataRefId1"));
    EXPECT_CALL(xPlaneDataRefSDKMock, findDataRef("dataRefId2"));
    command = Command("Test", "regex", {"dataRefId1", "dataRefId2"}, &xPlaneDataRefSDKMock);
}

//TEST_F(CommandTest, GetAltitudeValueFromCommand)
//{
//    EXPECT_CALL(xPlaneDataRefSDKMock, setValue(_, Eq(3500)));
//    Command c("Altitude", "^set altitude ((?:(?:\\d|zero|one|two|three|four|five|six|seven|eight|nine)\\s?){3,5})$", "dataRefId", &xPlaneDataRefSDKMock);
//
//    c.execute("set altitude three five zero zero");
//}

//TEST_F(CommandTest, GetAltimeterValueFromCommand)
//{
//    Command c("Altimeter", "^set altimeter ((?:(?:\\d|zero|one|two|three|four|five|six|seven|eight|nine)\\s?){3,5})$");
//    ASSERT_THAT(c.getValue("set altimeter two nine nine two"), Eq(29.92));
//}
