#ifndef X_COPILOT_INTCOMMANDEXECUTOR_H
#define X_COPILOT_INTCOMMANDEXECUTOR_H

#include "CommandExecutor.h"

class IntCommandExecutor : public CommandExecutor {
public:
    IntCommandExecutor(const std::string& value, const XPLMDataRef dataRef) : CommandExecutor(dataRef), value{parseToInt(value)} {};
    IntCommandExecutor(const std::string& value, const std::vector<XPLMDataRef> dataRefs) : CommandExecutor(dataRefs), value{parseToInt(value)} {};
    virtual void execute() const;
private:
    int value;
};


#endif //X_COPILOT_INTCOMMANDEXECUTOR_H
