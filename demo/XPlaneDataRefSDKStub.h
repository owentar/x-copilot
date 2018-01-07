#ifndef X_COPILOT_XPLANEDATAREFSDKSTUB_H
#define X_COPILOT_XPLANEDATAREFSDKSTUB_H

#include "XPlaneDataRefSDK.h"

using namespace xcopilot;

class XPlaneDataRefSDKStub : public XPlaneDataRefSDK {
public:
    virtual XPLMDataRef findDataRef(const std::string& name) { return nullptr; }
    virtual int getIntValue(XPLMDataRef id) const { return 0; }
    virtual void setValue(XPLMDataRef id, const int value) const {}
};


#endif //X_COPILOT_XPLANEDATAREFSDKSTUB_H
