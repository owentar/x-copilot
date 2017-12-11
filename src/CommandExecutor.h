#ifndef X_COPILOT_COMMANDEXECUTOR_H
#define X_COPILOT_COMMANDEXECUTOR_H

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "XPLMDataAccess.h"

typedef std::function<void(const std::string&, const std::vector<XPLMDataRef>&)> ExecutorFn;

class CommandExecutor {
public:
    enum Type { INT, FLOAT, DOUBLE };

    explicit CommandExecutor(const std::string value, const XPLMDataRef dataRef, const CommandExecutor::Type type)
            : dataRefs{dataRef}, valueAsWords{value}, doExecute{resolveExecutor(type)} {};
    explicit CommandExecutor(const std::string value, const std::vector<XPLMDataRef> dataRefs, const CommandExecutor::Type type)
            : dataRefs{dataRefs}, valueAsWords{value}, doExecute{resolveExecutor(type)} {};
    virtual ~CommandExecutor() = default;
    virtual void execute() const { doExecute(valueAsWords, dataRefs); };

protected:
    std::string valueAsWords;
    std::vector<XPLMDataRef> dataRefs;
    ExecutorFn doExecute;

private:
    ExecutorFn resolveExecutor(CommandExecutor::Type type) const;
};


#endif //X_COPILOT_COMMANDEXECUTOR_H
