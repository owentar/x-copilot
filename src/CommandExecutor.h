#ifndef X_COPILOT_COMMANDEXECUTOR_H
#define X_COPILOT_COMMANDEXECUTOR_H

#include <string>
#include <vector>

#include "XPLMDataAccess.h"
#include "utils.h"

class CommandExecutor {
public:
    explicit CommandExecutor(const XPLMDataRef dataRef) : dataRefs{dataRef} {};
    explicit CommandExecutor(const std::vector<XPLMDataRef> dataRefs) : dataRefs{dataRefs} {};
    virtual ~CommandExecutor() = default;
    virtual void execute() const = 0;

protected:
    std::vector<XPLMDataRef> dataRefs;
};


#endif //X_COPILOT_COMMANDEXECUTOR_H
