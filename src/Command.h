#ifndef COMMAND_H
#define COMMAND_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <vector>

#include "XPlaneDataRefSDK.h"

#include "CommandExecutor.h"

class Command
{
public:
    explicit Command(const std::string& name, const std::string& regExp, const std::vector<std::string>& dataRefs, XPlaneDataRefSDK* xPlaneDataRefSDK)
            : name{name}, commandRegExp{regExp, std::regex::icase}, dataRefsIds{}, xPlaneDataRefSDK{xPlaneDataRefSDK} {
        init(dataRefs);
    }
    explicit Command() = default;
    virtual ~Command() = default;
    virtual std::string getName() const { return name; }
    virtual bool isRecognized(const std::string&) const;
    virtual CommandExecutor getExecutor(const std::string&);

private:
    std::vector<XPLMDataRef> dataRefsIds;
    XPlaneDataRefSDK* xPlaneDataRefSDK;
    std::string name;
    std::regex commandRegExp;

    void init(const std::vector<std::string>& dataRefs) {
        std::transform(dataRefs.begin(), dataRefs.end(), std::back_inserter(dataRefsIds), [this](const std::string& dataRef) { return xPlaneDataRefSDK->findDataRef(dataRef); });
    }
};

#endif // COMMAND_H
