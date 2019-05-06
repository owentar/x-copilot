#include "CommandsConfigReader.h"

#include <algorithm>
#include <map>
#include <memory>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "CommandRecognizer.h"
#include "CommandMetadata.h"
#include "XPLMDataAccess.h"

using namespace xcopilot;
namespace pt = boost::property_tree;

static std::map<std::string, CommandType> commandTypeProvider = {
        {"int",     CommandType::INT},
        {"float",   CommandType::FLOAT},
        {"double",  CommandType::DOUBLE},
        {"boolean", CommandType::BOOLEAN}
};

std::vector<XPLMDataRef> readDataRefs(const pt::ptree &node, XPlaneDataRefSDK *xPlaneSDK) {
    std::vector<XPLMDataRef> dataRefsIds;
    std::transform(std::begin(node), std::end(node), std::back_inserter(dataRefsIds),
                   [xPlaneSDK](const pt::ptree::value_type &value) {
                       auto dataRef = value.second.get<std::string>("");
                       return xPlaneSDK->findDataRef(dataRef);
                   });
    return dataRefsIds;
}

std::vector<AircraftCommandsMatcher>
CommandsConfigReader::getAircraftCommandsMatchers(const std::string& indexFilePath) {
    pt::ptree root;
    pt::read_json(indexFilePath, root);
    std::vector<AircraftCommandsMatcher> matchers;

    for (auto &node : root) {
        auto id = node.first;
        auto author = node.second.get<std::string>("author");
        auto icao = node.second.get<std::string>("icao");
        auto description = node.second.get<std::string>("description");
        auto commandsFilePath = node.second.get<std::string>("commandsFilePath");
        matchers.push_back(AircraftCommandsMatcher{id, author, icao, description, commandsFilePath});
    }

    return matchers;
}

std::vector<std::shared_ptr<CommandRecognizer>> CommandsConfigReader::getCommandsFromFile(
        const std::string& commandsFilePath) {
    pt::ptree root;
    pt::read_json(commandsFilePath, root);
    std::vector<std::shared_ptr<CommandRecognizer>> commands;

    for (auto &node : root) {
        auto name = node.first;
        auto id = node.second.get<int>("id");
        auto type = node.second.get<std::string>("type");
        auto regex = node.second.get<std::string>("regex");
        auto dataRefs = readDataRefs(node.second.get_child("dataRefs"), xPlaneSDK);
        CommandMetadata commandMetadata(id, name, commandTypeProvider[type], regex, dataRefs);
        commands.push_back(std::make_shared<CommandRecognizer>(commandMetadata));
        std::cout << "CommandRecognizer: " << name << " - Regex: " << regex << std::endl;
    }

    return commands;
}
