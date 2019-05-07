#ifndef X_COPILOT_XPLANESDK_H
#define X_COPILOT_XPLANESDK_H

#include <string>

#include "XPLMDataAccess.h"

#include "defs.h"

namespace xcopilot {
    class EXPORT XPlaneDataRefSDK {
    public:
        virtual XPLMDataRef findDataRef(const std::string &name) { return XPLMFindDataRef(name.c_str()); };

        virtual int getIntValue(XPLMDataRef id) const { return XPLMGetDatai(id); };

        virtual void setValue(XPLMDataRef id, const int value) const { XPLMSetDatai(id, value); };
    };
}

#endif //X_COPILOT_XPLANESDK_H
