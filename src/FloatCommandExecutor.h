#ifndef X_COPILOT_FLOATCOMMANDEXECUTOR_H
#define X_COPILOT_FLOATCOMMANDEXECUTOR_H

#include "CommandExecutor.h"
#include "utils.h"

class FloatCommandExecutor : public CommandExecutor {
public:
    FloatCommandExecutor(const std::string& value, const XPLMDataRef dataRef) : CommandExecutor(dataRef), value{
            static_cast<float>(parseToDecimal(value, 0))} {};
    virtual void execute() const;
private:
    float value;
};


#endif //X_COPILOT_FLOATCOMMANDEXECUTOR_H
