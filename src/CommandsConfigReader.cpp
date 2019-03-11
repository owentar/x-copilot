#include "CommandsConfigReader.h"

#include <algorithm>
#include <map>
#include <memory>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "Command.h"

#ifdef RELEASE
#define COMMANDS_JSON_FILE_PATH "Resources/plugins/x-copilot/config/default-commands.json"
#else
#define COMMANDS_JSON_FILE_PATH "config/default-commands.json"
#endif

using namespace xcopilot;
namespace pt = boost::property_tree;

static std::map<std::string, CommandType> commandTypeProvider = {
    { "int", CommandType::INT },
    { "float", CommandType::FLOAT },
    { "double", CommandType::DOUBLE },
    { "boolean", CommandType::BOOLEAN }
};

boost::filesystem::path getDefaultCommandsFilePath()
{
	return boost::filesystem::absolute(COMMANDS_JSON_FILE_PATH);
}

std::vector<std::string> readDataRefs(const pt::ptree& node) {
    std::vector<std::string> dataRefs;
    std::transform(std::begin(node), std::end(node), std::back_inserter(dataRefs),
                   [](const pt::ptree::value_type& value) { return value.second.get<std::string>(""); });
    return dataRefs;
}

std::vector<std::shared_ptr<Command>> CommandsConfigReader::getCommandsForAircraft(const std::string author, const std::string icao, const std::string desc) {
	auto commandsFilePath = getDefaultCommandsFilePath().generic_string();
    pt::ptree root;
    pt::read_json(commandsFilePath, root);
    std::vector<std::shared_ptr<Command>> commands;

    for (auto& node : root) {
        auto name = node.first;
		auto id = node.second.get<int>("id");
        auto type = node.second.get<std::string>("type");
        auto regex = node.second.get<std::string>("regex");
        auto dataRefs = readDataRefs(node.second.get_child("dataRefs"));
        commands.push_back(std::make_shared<Command>(id, name, commandTypeProvider[type], regex, dataRefs, xPlaneSDK));
        std::cout << "Command: " << name << " - Regex: " << regex << std::endl;
    }

    return commands;
}
