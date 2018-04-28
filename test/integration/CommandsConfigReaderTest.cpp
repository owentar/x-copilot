#include "gmock/gmock.h"

#include "CommandsConfigReader.h"

using namespace testing;
using namespace xcopilot;

class XPlaneDataRefSDKMock : public XPlaneDataRefSDK
{
public:
    MOCK_METHOD1(findDataRef, XPLMDataRef(const std::string&));
    MOCK_CONST_METHOD1(getValue, int(XPLMDataRef));
    MOCK_CONST_METHOD2(setValue, void(XPLMDataRef, int));
};

class CommandsConfigReaderTest : public Test {
protected:
    NiceMock<XPlaneDataRefSDKMock> xPlaneDataRefSDKMock;
    CommandsConfigReader commandsConfigReader;

    CommandsConfigReaderTest() : xPlaneDataRefSDKMock{}, commandsConfigReader{&xPlaneDataRefSDKMock} {};
};

TEST_F(CommandsConfigReaderTest, GetDataRefsIdsWhenCommandIsConstructed)
{
    EXPECT_CALL(xPlaneDataRefSDKMock, findDataRef("dataRefId1"));
    EXPECT_CALL(xPlaneDataRefSDKMock, findDataRef("dataRefId2"));
    commandsConfigReader.getCommandsForAircraft("data/test-commands.json");
}
