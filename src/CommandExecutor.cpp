#include "CommandExecutor.h"

#include <map>

#include "utils.h"

using namespace xcopilot;

void executeBooleanCommand(const std::string& valueAsWords, const std::vector<XPLMDataRef>& dataRefs) {
    bool value = parseToBoolean(valueAsWords);
    std::for_each(dataRefs.begin(), dataRefs.end(), [value](const XPLMDataRef& id) { XPLMSetDatai(id, value ? 1 : 0); });
}

void executeFloatCommand(const std::string& valueAsWords, const std::vector<XPLMDataRef>& dataRefs) {
    float value = parseToFloat(valueAsWords);
    std::for_each(dataRefs.begin(), dataRefs.end(), [value](const XPLMDataRef& id) { XPLMSetDataf(id, value); });
}

void executeDoubleCommand(const std::string& valueAsWords, const std::vector<XPLMDataRef>& dataRefs) {
    double value = parseToDecimal(valueAsWords);
    std::for_each(dataRefs.begin(), dataRefs.end(), [value](const XPLMDataRef& id) { XPLMSetDatad(id, value); });
}

void executeIntCommand(const std::string& valueAsWords, const std::vector<XPLMDataRef>& dataRefs) {
    int value = parseToInt(valueAsWords);
    std::for_each(dataRefs.begin(), dataRefs.end(), [value](const XPLMDataRef& id) { XPLMSetDatai(id, value); });
}

static std::map<CommandType, ExecutorFn> executorProvider = {
        { CommandType::INT, executeIntCommand },
        { CommandType::FLOAT, executeFloatCommand },
        { CommandType::DOUBLE, executeDoubleCommand },
        { CommandType::BOOLEAN, executeBooleanCommand }
};

ExecutorFn CommandExecutor::resolveExecutor(const CommandType type) const {
    return executorProvider[type];
}
