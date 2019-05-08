#ifndef X_COPILOT_COMMANDEXECUTOR_H
#define X_COPILOT_COMMANDEXECUTOR_H

#include <functional>
#include <string>
#include <vector>

#include "defs.h"
#include "CommandType.h"
#include "XPLMDataAccess.h"
#include "CommandMetadata.h"

namespace xcopilot {
#ifdef IBM
	typedef std::function<void(const std::vector<int> &, const std::vector<XPLMDataRef> &)> ExecutorFn;
#else
    typedef std::function<void(const std::string &, const std::vector<XPLMDataRef> &)> ExecutorFn;
#endif
    

    class EXPORT CommandExecutor {
    public:
        explicit CommandExecutor(const CommandMetadata metadata, const std::string value)
                : metadata{metadata}, valueAsWords{value}, doExecute{resolveExecutor(metadata.getType())} {};

        explicit CommandExecutor(const CommandMetadata metadata, const std::vector<int> values)
                : metadata{metadata}, values{values}, doExecute{resolveExecutor(metadata.getType())} {};

        virtual ~CommandExecutor() = default;

#ifdef IBM
        virtual void execute() const { doExecute(values, metadata.getDataRefs()); };
#else
        virtual void execute() const { doExecute(valueAsWords, metadata.getDataRefs()); };
#endif

    protected:
        std::vector<int> values;
        std::string valueAsWords;
        CommandMetadata metadata;
        ExecutorFn doExecute;

    private:
        ExecutorFn resolveExecutor(xcopilot::CommandType type) const;
    };
}

#endif //X_COPILOT_COMMANDEXECUTOR_H
