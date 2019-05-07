#include "CommandExecutor.h"

#include <map>

#include "utils.h"

using namespace xcopilot;

#ifdef IBM
void executeBooleanCommand(const std::vector<int>& values, const std::vector<XPLMDataRef>& dataRefs) {
	bool value = parseToBoolean(values);
	std::for_each(dataRefs.begin(), dataRefs.end(), [value](const XPLMDataRef& id) { XPLMSetDatai(id, value ? 1 : 0); });
}

void executeFloatCommand(const std::vector<int>& values, const std::vector<XPLMDataRef>& dataRefs) {
	float value = parseToFloat(values);
	std::for_each(dataRefs.begin(), dataRefs.end(), [value](const XPLMDataRef& id) { XPLMSetDataf(id, value); });
}

void executeDoubleCommand(const std::vector<int>& values, const std::vector<XPLMDataRef>& dataRefs) {
	double value = parseToDecimal(values);
	std::for_each(dataRefs.begin(), dataRefs.end(), [value](const XPLMDataRef& id) { XPLMSetDatad(id, value); });
}

void executeIntCommand(const std::vector<int>& values, const std::vector<XPLMDataRef>& dataRefs) {
	int value = parseToInt(values);
	std::for_each(dataRefs.begin(), dataRefs.end(), [value](const XPLMDataRef& id) { XPLMSetDatai(id, value); });
}

static std::map<CommandType, ExecutorFn> executorProvider = {
    { CommandType::INT, executeIntCommand },
    { CommandType::FLOAT, executeFloatCommand },
    { CommandType::DOUBLE, executeDoubleCommand },
    { CommandType::BOOLEAN, executeBooleanCommand }
};
#else
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
#endif

ExecutorFn CommandExecutor::resolveExecutor(const CommandType type) const {
    return executorProvider[type];
}
