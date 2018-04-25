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
#include "CommandConfig.h"

namespace xcopilot {
    class Command {
    public:
        explicit Command(const CommandConfig config, XPlaneDataRefSDK *xPlaneDataRefSDK)
                : config{config}, xPlaneDataRefSDK{xPlaneDataRefSDK} {
            init(config.getDataRefs());
        }

        explicit Command() = default;

        virtual ~Command() = default;

        virtual std::string getName() const { return config.getName(); }

        virtual bool isRecognized(const std::string &) const;

        virtual CommandExecutor getExecutor(const std::string &);

    private:
        std::vector<XPLMDataRef> dataRefsIds;
        XPlaneDataRefSDK *xPlaneDataRefSDK;
        CommandConfig config;

        void init(const std::vector<std::string> &dataRefs) {
            std::transform(dataRefs.begin(), dataRefs.end(), std::back_inserter(dataRefsIds),
                           [this](const std::string &dataRef) { return xPlaneDataRefSDK->findDataRef(dataRef); });
        }
    };
}

#endif // COMMAND_H
