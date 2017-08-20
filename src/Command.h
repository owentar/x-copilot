#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <regex>

class Command
{
    public:
        explicit Command(const std::string& name, const std::string& regExp) : name{name}, commandRegExp{regExp} {};
        virtual ~Command() {};
        virtual bool isRecognized(const std::string&) const;
        virtual int getValue(const std::string&) const;

    private:
        std::string name;
        std::regex commandRegExp;
};

#endif // COMMAND_H
