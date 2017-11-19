#include <algorithm>

#include "IntCommandExecutor.h"

#include "XPLMDataAccess.h"

void IntCommandExecutor::execute() const {
    std::for_each(dataRefs.begin(), dataRefs.end(), [this](const XPLMDataRef& id) { XPLMSetDatai(id, value); });
}