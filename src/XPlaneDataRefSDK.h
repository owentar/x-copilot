#ifndef X_COPILOT_XPLANESDK_H
#define X_COPILOT_XPLANESDK_H

#include <string>

#include "XPLMDataAccess.h"

namespace xcopilot {
    class XPlaneDataRefSDK {
    public:
        virtual XPLMDataRef findDataRef(const std::string &name) { return nullptr; };

        virtual int getIntValue(XPLMDataRef id) const { return XPLMGetDatai(id); };

        virtual void setValue(XPLMDataRef id, const int value) const { XPLMSetDatai(id, value); };
    };
}

#endif //X_COPILOT_XPLANESDK_H
