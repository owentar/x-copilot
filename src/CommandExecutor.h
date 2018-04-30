#ifndef X_COPILOT_COMMANDEXECUTOR_H
#define X_COPILOT_COMMANDEXECUTOR_H

#include <functional>
#include <string>
#include <vector>

#include "CommandType.h"
#include "XPLMDataAccess.h"
#include "CommandMetadata.h"

namespace xcopilot {
    typedef std::function<void(const std::string &, const std::vector<XPLMDataRef> &)> ExecutorFn;

    class CommandExecutor {
    public:
        explicit CommandExecutor(const CommandMetadata metadata, const std::string value)
                : metadata{metadata}, valueAsWords{value}, doExecute{resolveExecutor(metadata.getType())} {};

        virtual ~CommandExecutor() = default;

        virtual void execute() const { doExecute(valueAsWords, metadata.getDataRefs()); };

    protected:
        std::string valueAsWords;
        CommandMetadata metadata;
        ExecutorFn doExecute;

    private:
        ExecutorFn resolveExecutor(xcopilot::CommandType type) const;
    };
}

#endif //X_COPILOT_COMMANDEXECUTOR_H
