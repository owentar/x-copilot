#ifndef X_COPILOT_COMMANDEXECUTOR_H
#define X_COPILOT_COMMANDEXECUTOR_H

#include <functional>
#include <string>
#include <vector>

#include "CommandType.h"
#include "XPLMDataAccess.h"

namespace xcopilot {
    typedef std::function<void(const std::vector<int> &, const std::vector<XPLMDataRef> &)> ExecutorFn;

    class CommandExecutor {
    public:
        explicit CommandExecutor(const std::string value, const XPLMDataRef dataRef, const xcopilot::CommandType type)
                : dataRefs{dataRef}, valueAsWords{value}, doExecute{resolveExecutor(type)} {}

        explicit CommandExecutor(const std::string value, const std::vector<XPLMDataRef> dataRefs,
                                 const xcopilot::CommandType type)
                : dataRefs{dataRefs}, valueAsWords{value}, doExecute{resolveExecutor(type)} {};

		explicit CommandExecutor(const std::vector<int> values, const std::vector<XPLMDataRef> dataRefs,
			const xcopilot::CommandType type)
			: dataRefs{ dataRefs }, values{ values }, doExecute{ resolveExecutor(type) } {};

        virtual ~CommandExecutor() = default;

        virtual void execute() const { doExecute(values, dataRefs); };

    protected:
		std::vector<int> values;
        std::string valueAsWords;
        std::vector<XPLMDataRef> dataRefs;
        ExecutorFn doExecute;

    private:
        ExecutorFn resolveExecutor(xcopilot::CommandType type) const;
    };
}

#endif //X_COPILOT_COMMANDEXECUTOR_H
