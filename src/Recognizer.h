#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include <memory>
#include <vector>

#include "Command.h"

namespace xcopilot {
	class __declspec(dllexport) Recognizer {
	public:
		virtual ~Recognizer() = default;

		virtual void configure(const std::vector<std::shared_ptr<Command>>& commands) { this->commands = commands; }
		virtual void start() = 0;
		virtual void stop() = 0;
		virtual std::vector<CommandExecutor> getRecognizedCommands() = 0;
	protected:
		std::vector<std::shared_ptr<Command>> commands;
	};
}

#endif // RECOGNIZER_H
