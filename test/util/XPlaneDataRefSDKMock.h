#ifndef X_COPILOT_XPLANEDATAREFSDKMOCK_H
#define X_COPILOT_XPLANEDATAREFSDKMOCK_H

#include "gmock/gmock.h"

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

#endif //X_COPILOT_XPLANEDATAREFSDKMOCK_H
