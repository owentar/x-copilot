#include "gmock/gmock.h"

#include "Command.h"
#include "CommandConfig.h"
#include "XPlaneDataRefSDK.h"

using namespace testing;
using namespace xcopilot;

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

    CommandTest() : xPlaneDataRefSDKMock{}, command(CommandConfig("Test", CommandType::FLOAT, "^.*test$", {"dataRefId"}), &xPlaneDataRefSDKMock) {};
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
    command = Command(CommandConfig("Test", CommandType::FLOAT, "regex", {"dataRefId1", "dataRefId2"}), &xPlaneDataRefSDKMock);
}
