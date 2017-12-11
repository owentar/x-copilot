#include "CommandExecutor.h"

#include "utils.h"

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

static std::map<CommandExecutor::Type, ExecutorFn> executorProvider = {
        { CommandExecutor::Type::INT, executeIntCommand },
        { CommandExecutor::Type::FLOAT, executeFloatCommand },
        { CommandExecutor::Type::DOUBLE, executeDoubleCommand }
};

ExecutorFn CommandExecutor::resolveExecutor(const CommandExecutor::Type type) const {
    return executorProvider[type];
}
