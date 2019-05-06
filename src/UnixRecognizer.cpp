#include "UnixRecognizer.h"

#include <boost/format.hpp>

#include "Logger.h"

using namespace xcopilot;
using boost::format;

void UnixRecognizer::start()
{
    pocketsphinx->start();
    microphone->start(this);
}

void UnixRecognizer::stop()
{
    pocketsphinx->stop();
    microphone->stop();
}

void UnixRecognizer::handleAudio(const short* rawData, unsigned long frameCount)
{
    pocketsphinx->process(rawData, frameCount);

    if (pocketsphinx->isSpeaking())
    {
        shouldDecode = true;
    }
    else
    {
        if (shouldDecode)
        {
            shouldDecode = false;
            recognizeCommand(pocketsphinx->decode());
        }
    }
}

void UnixRecognizer::recognizeCommand(const std::string& phrase)
{
    Logger::getInstance()->debug(format("Processing: %1%") % phrase);
    auto value = std::find_if(commands.begin(), commands.end(),
                              [phrase] (const std::shared_ptr<CommandRecognizer> command) -> bool { return command->commandRecognized(phrase); });
    if (value != commands.end()) {
        Logger::getInstance()->debug(format("CommandRecognizer recognized: %1%") % (*value)->getName());
        commandsRecognized.push_back((*value)->getExecutor(phrase));
    }
}

std::vector<CommandExecutor> UnixRecognizer::getRecognizedCommands()
{
    auto commands = commandsRecognized;
    commandsRecognized.clear();
    return commands;
}
