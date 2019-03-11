#ifndef COMMAND_H
#define COMMAND_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <vector>

#include "CommandExecutor.h"
#include "XPlaneDataRefSDK.h"

namespace xcopilot {
    class Command {
    public:
        explicit Command(const int id, const std::string &name, const CommandType type, const std::string &regExp,
						 const std::vector<std::string> &dataRefs, XPlaneDataRefSDK *xPlaneDataRefSDK)
    		: id{ id }, name{ name }, type{ type }, commandRegExp{ regExp, std::regex::icase }, dataRefsIds{},
                  xPlaneDataRefSDK{xPlaneDataRefSDK} {
            init(dataRefs);
        }

        explicit Command() = default;

        virtual ~Command() = default;

		virtual int getId() const { return id; }

        virtual std::string getName() const { return name; }

        virtual bool isRecognized(const std::string &) const;

        virtual CommandExecutor getExecutor(const std::string &);

		CommandExecutor getExecutor(const std::vector<int>&);

    private:
		int id;
        std::vector<XPLMDataRef> dataRefsIds;
        XPlaneDataRefSDK *xPlaneDataRefSDK;
        std::string name;
        CommandType type;
        std::regex commandRegExp;

        void init(const std::vector<std::string> &dataRefs) {
            std::transform(dataRefs.begin(), dataRefs.end(), std::back_inserter(dataRefsIds),
                           [this](const std::string &dataRef) { return xPlaneDataRefSDK->findDataRef(dataRef); });
        }
    };
}

#endif // COMMAND_H
