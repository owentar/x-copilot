#ifndef COMMAND_H
#define COMMAND_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <regex>
#include <vector>

#include "XPlaneDataRefSDK.h"

#include "CommandExecutor.h"

typedef std::shared_ptr<CommandExecutor> CommandExecutorPtr;

class Command
{
public:
    explicit Command(const std::string& name, const std::string& regExp, const std::string& dataRef, XPlaneDataRefSDK* xPlaneDataRefSDK)
            : name{name}, commandRegExp{regExp, std::regex::icase}, xPlaneDataRefSDK{xPlaneDataRefSDK}, dataRefsIds{} {
        init({dataRef});
    }
    explicit Command(const std::string& name, const std::string& regExp, const std::string& dataRef)
            : name{name}, commandRegExp{regExp, std::regex::icase}, xPlaneDataRefSDK{}, dataRefsIds{} {
        init({dataRef});
    }
    explicit Command(const std::string& name, const std::string& regExp, const std::vector<std::string> dataRefs)
            : name{name}, commandRegExp{regExp, std::regex::icase}, dataRefsIds{} {
        init(dataRefs);
    }
    explicit Command() {}
    virtual ~Command() {};
    virtual bool isRecognized(const std::string&) const;
    virtual CommandExecutorPtr getExecutor(const std::string&);

private:
    std::vector<XPLMDataRef> dataRefsIds;
    XPlaneDataRefSDK* xPlaneDataRefSDK;
    std::string name;
    std::regex commandRegExp;

    void init(const std::vector<std::string> dataRefs) {
//        dataRefsIds.resize(dataRefs.size());
//        std::cout << dataRefsIds.size() << std::endl;
//        std::for_each(dataRefsIds.begin(), dataRefsIds.end(), [this](const XPLMDataRef id) { std::cout << id << std::endl; });
        std::transform(dataRefs.begin(), dataRefs.end(), std::back_inserter(dataRefsIds), [this](const std::string& dataRef) { return xPlaneDataRefSDK->findDataRef(dataRef); });
    }
};

#endif // COMMAND_H
