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
#include "CommandMetadata.h"

namespace xcopilot {
    class Command {
    public:
        explicit Command(const CommandMetadata metadata, XPlaneDataRefSDK *xPlaneDataRefSDK)
                : metadata{metadata}, xPlaneDataRefSDK{xPlaneDataRefSDK} {
            init(metadata.getDataRefs());
        }

        explicit Command() = default;

        virtual ~Command() = default;

        virtual std::string getName() const { return metadata.getName(); }

        virtual bool isRecognized(const std::string &) const;

        virtual CommandExecutor getExecutor(const std::string &);

    private:
        std::vector<XPLMDataRef> dataRefsIds;
        XPlaneDataRefSDK *xPlaneDataRefSDK;
        CommandMetadata metadata;

        void init(const std::vector<std::string> &dataRefs) {
            std::transform(dataRefs.begin(), dataRefs.end(), std::back_inserter(dataRefsIds),
                           [this](const std::string &dataRef) { return xPlaneDataRefSDK->findDataRef(dataRef); });
        }
    };
}

#endif // COMMAND_H
