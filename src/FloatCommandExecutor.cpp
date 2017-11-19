#include <algorithm>

#include "FloatCommandExecutor.h"

void FloatCommandExecutor::execute() const {
    std::for_each(dataRefs.begin(), dataRefs.end(), [this](const XPLMDataRef& id) { XPLMSetDataf(id, value); });
}